/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:25:04 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/01 12:42:24 by marirodr         ###   ########.fr       */
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
	if (philo->table->nb_must_eat == 0)
		return (NULL);
	return (NULL);
}

void	*ft_sleep(t_philo *philo)
{
	return (NULL);
}

void	*ft_think(t_philo *philo)
{
	return (NULL);
}
