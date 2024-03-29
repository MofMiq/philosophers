/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_n_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:46:17 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/09 18:34:47 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*This is a simple funtion to print different error messages.*/

void	ft_print_error(int error)
{
	if (error == WRONG_NBR)
		printf("Error! The number of arguments is wrong, must be 4 or 5\n");
	else if (error == BAD_IMPUT)
		printf("Error! All arguments must be numbers\n");
	else if (error == EXCED_LIMT)
		printf("Error! The number must be positive, between 1 and 200\n");
	else if (error == MALLOC_FAIL)
		printf("Error! Failed to allocate memory\n");
	else if (error == MUTEX)
		printf("Error! Failed to create mutexs\n");
	else if (error == THREAD)
		printf("Error! Failed to create threads\n");
	exit(1);
}

/*This function prints out each action that every philosopher can perform
during the execution of the program.*/

void	ft_print_msg(t_philo *philo, int i)
{
	if (i == 1 && !ft_must_stop(philo->table))
		printf("%s[%lld] %d has taken a fork%s\n", YELLOW, \
			ft_current_time(philo->table), philo->id, END);
	else if (i == 2)
		printf("%s[%lld] %d died%s\n", RED, \
			ft_current_time(philo->table), philo->id, END);
	else if (i == 3 && !ft_must_stop(philo->table))
		printf("%s[%lld] %d is eating%s\n", PURPLE, \
			ft_current_time(philo->table), philo->id, END);
	else if (i == 4 && !ft_must_stop(philo->table))
		printf("%s[%lld] %d is sleeping %s\n", BLUE, \
			ft_current_time(philo->table), philo->id, END);
	else if (i == 5 && !ft_must_stop(philo->table))
		printf("%s[%lld] %d is thinking%s\n", PINK, \
			ft_current_time(philo->table), philo->id, END);
}

/*Free every mutex created as forks for each philosopher.*/

void	ft_free_forks_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

/*Free every resource needed: structures, mutexes and threads.
For threads, we call pthread_join() function, that is used to make the
program wait until the threads have finished executing and the resources
associated with that thread will be freed.*/

void	ft_free_all(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(philo[i].mutex_eat);
		free(philo[i].mutex_eat);
		i++;
	}
	ft_free_forks_mutex(table);
	pthread_mutex_destroy(table->mutex_table);
	free(table->mutex_table);
	free(philo);
}
