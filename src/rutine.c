/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:25:04 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/01 17:21:58 by marirodr         ###   ########.fr       */
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

void	*ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		printf("PAR INDICE FORK!!!!! %d\n", philo->indice[1]);//erase
		ft_print_msg(philo, 1);
		pthread_mutex_lock(philo->l_fork);
		printf("par INDICE FORK!!!!! %d\n", philo->indice[0]);//erase
		ft_print_msg(philo, 1);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		printf("IMPAR INDICE FORK!!!!! %d\n", philo->indice[0]);//erase
		ft_print_msg(philo, 1);
		pthread_mutex_lock(philo->r_fork);
		printf("impar INDICE FORK!!!!! %d\n", philo->indice[1]);//erase
		ft_print_msg(philo, 1);
	}
	ft_print_msg(philo, 3);
	philo->last_eat = ft_current_time(philo->table);
	while (ft_current_time(philo->table) < philo->last_eat + philo->table->time_to_eat)
	{
		//aqui iria condicion de comprobar si algun otro filo ha muerto;
		usleep(10);
	}
	philo->cur_eat++;
	//comprobar por si hay limite argumento 5
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	*ft_sleep(t_philo *philo)
{
	long long	sleep;

	ft_print_msg(philo, 4);
	sleep = ft_current_time(philo->table);
	while (ft_current_time(philo->table) < sleep + philo->table->time_to_sleep)
	{
		//aqui iria condicion de comprobar si algun otro filo ha muerto;
		usleep(10);
	}
	return (NULL);
}

void	*ft_think(t_philo *philo)
{
	long long	think;
	long long	time;

	ft_print_msg(philo, 5);
	think = (philo->table->time_to_die - (philo->table->time_to_eat + philo->table->time_to_sleep)) / 2;
	time = ft_current_time(philo->table);
	//casos particulares a raiz del resultado de think??
	while (ft_current_time(philo->table) < time + think)
	{
		//aqui iria condicion de comprobar si algun otro filo ha muerto;
		usleep(10);
	}
	return (NULL);
}
