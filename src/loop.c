/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:33:17 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/09 10:18:26 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*si comento los mutex_table me dan pecha de warnings de data race cuango
compilo con fsanitize pero el caso "base" de muerte (4 310 200 100) sigue
funcionando.
en cambio si descomento los mutex_table, se me reducen pecha los warning -solo
me queda aparentemente 1 en ft_is_dead- pero el caso "base" de muerte deja
de funcionar, no termina y sale data race en ft_is_dead
en ft_is_dead hhay aparentemente data race en cualquier caso*/

/*This function continuously checks whether any of the variables that determine
the program's state have changed. First, we verify if "finished" is equal to
the total number of philosophers, which is the case when a fifth argument
specifies how many times each of them must eat. Additionally, we monitor for
any philosopher's demise. If either of these conditions becomes true, the
simulation must halt immediately.*/

int	ft_must_stop(t_table *table)
{
	pthread_mutex_lock(table->mutex_table);
	if (table->finished == table->nbr_philo || table->dead == 1)
	{
		pthread_mutex_unlock(table->mutex_table);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(table->mutex_table);
		return (0);
	}
}

/*This function is responsible for checking whether a philosopher has passed
away and modifies the variable that informs the simulation about this occurrence.
We employ mutexes to update the 'dead' value in a manner that prevents
conflicting access among different threads.
To calculate the time when a philosopher should perish, we obtain the current
simulation time and subtract the last time the philosopher dined. If the result
is equal to or exceeds the 'time_to_die', it signifies that the philosopher
hasn't consumed a meal within the time required to survive.*/

int	ft_is_dead(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(philo->table->mutex_table);
	pthread_mutex_lock(philo->mutex_eat);
	time = (ft_current_time(philo->table) - philo->last_eat);
	pthread_mutex_unlock(philo->mutex_eat);
	if (time >= philo->table->time_to_die)
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

/*This function is designed to keep the program running until one of the
two conditions causes it to stop (see ft_must_stop()).*/

void	ft_infinite_loop(t_philo *philo, t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->nbr_philo) //data race aqui
		{
			if (ft_is_dead(&philo[i]))
				break ;
			i++;
		}
		if (ft_must_stop(table))
			break ;
		usleep(100);
	}
	return ;
}

/*This is the function responsible for initiating and orchestrating the
sequence of the philosophers' routines - eating, sleeping, and thinking -
while continuously checking if the simulation should halt. Furthermore, we
perform a few checks, prevent negative time values at the beginning of the
simulation due to the delay introduced in ft_create_thread(), and ensure
that even-numbered philosophers are created slightly later to avoid
potential deadlocks.*/

void	*ft_rutine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->table->nb_must_eat == 0)
		return (NULL);
	if (philo->table->time_to_die == 0)
		return (NULL);
	while (ft_current_time(philo->table) < 0)
	{
		pthread_mutex_lock(philo->mutex_eat);
		philo->last_eat = ft_current_time(philo->table);
		pthread_mutex_unlock(philo->mutex_eat);
		usleep(20);
	}
	if (philo->id % 2 == 0)
		usleep(50);
	while (!ft_must_stop(philo->table))
	{
		if (!ft_must_stop(philo->table))
			ft_eat(philo);
		else 
			break ;
		if (!ft_must_stop(philo->table))
			ft_sleep(philo);
		else
			break ;
		if (!ft_must_stop(philo->table))
			ft_think(philo);
	}
	return (NULL);
}

/*This function will be responsible for both creating the threads representing
each philosopher and keeping the main program running. To create the threads,
we use the pthread_create() function, which starts the execution of the function
passed as the third parameter and stores the thread identifier in the variable
provided as the first argument.
When creating multiple philosophers, we introduce a small delay before initiating
the simulation's execution. This delay allows time for all threads to be created
and start simultaneously.*/

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
			if ((pthread_create(&philo[i].thread, NULL, ft_rutine, \
				&philo[i])) != 0)
				ft_print_error(THREAD);
			printf("Direccion de memoria del hilo con tid %d: %p\n", philo[i].id, &philo[i].thread);
			i++;
		}
		ft_infinite_loop(philo, table);
		ft_free_all(philo, table);
	}
}
