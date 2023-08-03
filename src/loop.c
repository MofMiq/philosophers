/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:33:17 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/03 12:05:37 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_must_stop(t_table *table)
{
	if (table->finished == table->nbr_philo || table->dead == 1)
		return (1);
	return (0);
}

//ft_print_msg(philo, 2); ?? porque cuando lo pongo aqui si va

int	ft_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->table->mutex_table);
	if ((ft_current_time(philo->table) - philo->last_eat) >= \
		philo->table->time_to_die)
	{
		ft_print_msg(philo, 2);
		philo->table->dead = 1;
		pthread_mutex_unlock(philo->table->mutex_table);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->table->mutex_table);
		return (0);
	}
}

void	ft_infinite_loop(t_philo *philo, t_table *table)
{
	while (1)
	{
		if (ft_must_stop(table) || ft_is_dead(philo))
			break ;
		usleep(1);
	}
	return ;
}

void	*ft_testing(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->table->nb_must_eat == 0)
		return (NULL);
	if (philo->table->time_to_die == 0)
		return (NULL);
	while (ft_current_time(philo->table) < 0)
	{
		philo->last_eat = ft_current_time(philo->table);
		usleep(1);
	}
	if (philo->id % 2 == 0)
		usleep(50);
	while (!ft_must_stop(philo->table) && philo->table->dead == 0)
	{
		if (!ft_must_stop(philo->table) && philo->table->dead == 0)
			ft_eat(philo);
		if (!ft_must_stop(philo->table) && philo->table->dead == 0)
			ft_sleep(philo);
		if (!ft_must_stop(philo->table) && philo->table->dead == 0)
			ft_think(philo);
	}
	return (NULL);
}

//usleep(10); pequeño delay entre el ft_infinite_loop & ft_free_all

void	ft_create_thread(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_philo == 1)
	{
		table->time_start = ft_get_system_time();
		if ((pthread_create(&philo[i].thread, NULL, ft_one_philo, \
			&philo[i])) != 0)
			ft_print_error(THREAD);
		ft_free_all(philo, table);
	}
	else
	{
		table->time_start = ft_get_system_time() + table->nbr_philo * 20;
		while (i < table->nbr_philo)
		{
			if ((pthread_create(&philo[i].thread, NULL, ft_testing, \
				&philo[i])) != 0)
				ft_print_error(THREAD);
			i++;
		}
		ft_infinite_loop(philo, table);
		ft_free_all(philo, table);
	}
}
