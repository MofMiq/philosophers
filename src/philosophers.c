/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:42:59 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/04 11:44:30 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*Right after arranging the table, we proceed to "arrange" the forks. To
accomplish this, we allocate memory for the forks, as there is one for each
seated philosopher. Since our forks themselves act as mutexes, we utilize the
pthread_mutex_init() function from the pthread.h library to initialize them.

A mutex a type of primitive synchronization and essentially functions as a
"lock" that allows us to control access to the data and prevent those shared
resources from being used simultaneously.
It takes a pointer to a variable of type pthread_mutex_t and another pointer
to specify specific attributes. The function returns 0 if the mutex is
successfully created.*/

void	ft_init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philo);
	if (!table->forks)
		ft_print_error(MALLOC_FAIL);
	while (i < table->nbr_philo)
	{
		if ((pthread_mutex_init(&table->forks[i], NULL)) != 0)
		{
			ft_free_forks_mutex(table);
			ft_print_error(MUTEX);
		}
		printf("Direccion de memoria del mutex %d: %p\n", i, &table->forks[i]);
		i++;
	}
}

/*Once we confirm that the arguments are valid, we proceed to initialize
the t_table structure, which symbolically represents the table where the
philosophers will be seated. Here are the variables that are shared among all
the philosophers.*/

void	ft_init_table(int argc, char **argv, t_table *table)
{
	table->nbr_philo = ft_atol(argv[1]);
	if (table->nbr_philo < 1 || table->nbr_philo > 200)
		ft_print_error(EXCED_LIMT);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		table->nb_must_eat = ft_atol(argv[5]);
		/*if (table->nb_must_eat == 0)
			ft_print_error(EXCED_LIMT);*/
	}
	else
		table->nb_must_eat = -1;
	table->finished = 0;
	table->dead = 0;
	table->mutex_table = malloc(sizeof(pthread_mutex_t));
	if (!table->mutex_table)
		ft_print_error(MALLOC_FAIL);
	if ((pthread_mutex_init(table->mutex_table, NULL)) != 0)
		ft_print_error(MUTEX);
	printf("Direccion de memoria del mutex_table : %p\n", &table->mutex_table);
	ft_init_forks(table);
}

/* 
Once the table and forks are set, we proceed to initialize the t_philo
structure- for which we have previously allocated memory. We assign an ID to
each philosopher, numbering them from 1 to the total count. Additionally, we
assign the table to the structure to retain its reference, and we allocate
the forks that each philosopher will use for eating. Specifically, each
philosopher takes hold of their "own" fork and the one next to it (n + 1),
except for the last philosopher who takes the first fork placed on the table.
			 		[1]
			 ---------
	 		|	1		 	 0|
	 [2]|				 	|	[4]
	 		|	2			 3|
			 ---------
			 		[3]
*/

void	ft_init_philosophers(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].cur_eat = 0;
		philo[i].last_eat = 0;
		philo[i].table = table;
		if (philo[i].id == table->nbr_philo)
		{
			philo[i].l_fork = &table->forks[i];
			philo[i].r_fork = &table->forks[0];
		}
		else
		{
			philo[i].l_fork = &table->forks[i];
			philo[i].r_fork = &table->forks[i + 1];
		}
		i++;
	}
}

void	ft_leaks(void)
{
	system("leaks -q philo");
}

//atexit(ft_leaks);
/*To start the program, we are going to make sure that the arguments are
correct, initialize both structures and create the threads.*/

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		ft_print_error(WRONG_NBR);
	ft_check_arg(argv);
	ft_init_table(argc, argv, &table);
	philo = malloc(sizeof(t_philo) * table.nbr_philo);
	if (!philo)
		ft_print_error(MALLOC_FAIL);
	ft_init_philosophers(philo, &table);
	ft_create_thread(philo, &table);
}
