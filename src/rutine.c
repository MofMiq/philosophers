/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:25:04 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/02 13:50:39 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*ft_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nb_must_eat == 0)
		return (NULL);
	if (philo->table->time_to_die == 0)
		return (NULL);
	philo->last_eat = ft_current_time(philo->table);
	pthread_mutex_lock(&philo->table->forks[0]);
	ft_print_msg(philo, 1);
	pthread_mutex_unlock(&philo->table->forks[0]);
	while ((ft_current_time(philo->table) + philo->last_eat) < philo->table->time_to_die)
		usleep(10);
	ft_print_msg(philo, 2);
	return (NULL);
}

/*los filosofos se sientan en sentido antihorario.
colocan "su" tenedor a la izquierda (id - 1).
los diestros empiezan cogiendo el tenedor a su derecha (id).
los zurdos empiezan cogiendo el tenedor a su izquierda (id - 1).*/

void	*ft_eat(t_philo *philo)
{
	if (ft_must_stop(philo->table) || philo->table->dead == 1)
		return (NULL);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		//printf("DIESTRO COJE 1er TENEDOR A DERECHA!!!!! %d\n", philo->indice[1]);//erase
		ft_print_msg(philo, 1);
		pthread_mutex_lock(philo->l_fork);
		//printf("DIESTRO COJE 2o TENEDOR A IZQUIERDA!!!!! %d\n", philo->indice[0]);//erase
		ft_print_msg(philo, 1);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		//printf("ZURDO COJE 1er TENEDOR A IZQUIERDA!!!!! %d\n", philo->indice[0]);//erase
		ft_print_msg(philo, 1);
		pthread_mutex_lock(philo->r_fork);
		//printf("ZURDO COJE 2o TENEDOR A DERECHA!!!!! %d\n", philo->indice[1]);//erase
		ft_print_msg(philo, 1);
	}
	ft_print_msg(philo, 3);
	philo->last_eat = ft_current_time(philo->table);
	while (!ft_must_stop(philo->table) && (ft_current_time(philo->table) < philo->last_eat + philo->table->time_to_eat))
	{
		if (philo->table->dead == 1)
			break ;
		usleep(10);
	}
	philo->cur_eat++;
	//printf("%d VECES QUE A COMIDO %d PHILO\n", philo->cur_eat, philo->id);
	if (philo->cur_eat == philo->table->nb_must_eat) //??
	{
		pthread_mutex_lock(philo->table->mutex_table);
		philo->table->finished++;
		pthread_mutex_unlock(philo->table->mutex_table);
	}
	//printf("%d FILOSOFOS HAN COMIDO SUFICIENTEMENTE\n", philo->table->finished);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	*ft_sleep(t_philo *philo)
{
	long long	sleep;

	if (ft_must_stop(philo->table) || philo->table->dead == 1)
		return (NULL);
	ft_print_msg(philo, 4);
	sleep = ft_current_time(philo->table);
	while (!ft_must_stop(philo->table) && (ft_current_time(philo->table) < sleep + philo->table->time_to_sleep))
	{
		if (philo->table->dead == 1)
			break ;
		usleep(10);
	}
	return (NULL);
}

void	*ft_think(t_philo *philo)
{
	long long	think;
	long long	time;

	if (ft_must_stop(philo->table) || ft_is_dead(philo))
		return (NULL);
	ft_print_msg(philo, 5);
	think = (philo->table->time_to_die - (philo->table->time_to_eat + philo->table->time_to_sleep)) / 2;
	time = ft_current_time(philo->table);
	//casos particulares a raiz del resultado de think??
	while (!ft_must_stop(philo->table) && (ft_current_time(philo->table) < time + think))
	{
		if (philo->table->dead == 1)
			break ;
		usleep(10);
	}
	return (NULL);
}
