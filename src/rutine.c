/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:25:04 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/08 19:11:01 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*Routine for a single philosopher, created solely to verify the functionality
of a simple routine when I started the project.*/

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
	while ((ft_current_time(philo->table) + philo->last_eat) \
		< philo->table->time_to_die)
		usleep(100);
	ft_print_msg(philo, 2);
	return (NULL);
}

/*With this function, we will make the philosophers either right-handed or
left-handed, meaning we will designate that philosophers with even IDs pick up
the right fork first, followed by the left one, and vice versa for philosophers
with odd IDs. We do this to prevent deadlocks right from the start of the
simulation. If all philosophers were to pick up either the right or left fork,
they would be left waiting without eating until they die.*/

void	ft_right_or_left_handed(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		ft_print_msg(philo, 1);
		if (ft_must_stop(philo->table))
			return ;
		pthread_mutex_lock(philo->l_fork);
		ft_print_msg(philo, 1);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		ft_print_msg(philo, 1);
		if (ft_must_stop(philo->table))
			return ;
		pthread_mutex_lock(philo->r_fork);
		ft_print_msg(philo, 1);
	}
}

/*This function is designed for each philosopher to "eat." To achieve this,
we determine which fork the philosopher should pick up first using another
function (see ft_right_or_left_handed()), update a variable that stores the
last time a philosopher ate (crucial for checking a philosopher's demise). In
case a fifth argument isn't provided, we keep track of the number of times
each philosopher has eaten, as well as those who have consumed their required
meals. We wait for the philosopher to finish eating (time_to_eat), and
ultimately, we unlock the mutexes of the forks.*/

void	*ft_eat(t_philo *philo)
{
	ft_right_or_left_handed(philo);
	ft_print_msg(philo, 3);
	pthread_mutex_lock(philo->mutex_eat);
	philo->last_eat = ft_current_time(philo->table);
	pthread_mutex_unlock(philo->mutex_eat);
	philo->cur_eat++;
	if (philo->cur_eat == philo->table->nb_must_eat)
	{
		pthread_mutex_lock(philo->table->mutex_table);
		philo->table->finished++;
		pthread_mutex_unlock(philo->table->mutex_table);
	}
	while (!ft_must_stop(philo->table) && (ft_current_time(philo->table) \
		< philo->last_eat + philo->table->time_to_eat))
		usleep(100);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

/*This function is designed for every philosopher to "sleep" and
essentially wait until they "wake up" (time_to_sleep).*/

void	*ft_sleep(t_philo *philo)
{
	long long	s;

	ft_print_msg(philo, 4);
	s = ft_current_time(philo->table);
	while (!ft_must_stop(philo->table)
		&& (ft_current_time(philo->table) < s + philo->table->time_to_sleep))
		usleep(100);
	return (NULL);
}

/*This function is designed for every philosopher to "think," and it is
very similar to the sleeping function.
The only difference is that we need to calculate the thinking time for each
philosopher ourselves. I calculate it proportionally based on the other three
time intervals and divide it accordingly, ensuring that a philosopher never
spends either too much or too little time thinking.*/

void	*ft_think(t_philo *philo)
{
	long long	think;
	long long	time;

	ft_print_msg(philo, 5);
	think = (philo->table->time_to_die - (philo->table->time_to_eat \
		+ philo->table->time_to_sleep)) / 2;
	time = ft_current_time(philo->table);
	while (!ft_must_stop(philo->table)
		&& (ft_current_time(philo->table) < time + think))
		usleep(100);
	return (NULL);
}
