/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:42:59 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/03 13:09:35 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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
		i++;
	}
}

void	ft_init_table(int argc, char **argv, t_table *table)
{
	table->nbr_philo = ft_atol(argv[1]);
	if (table->nbr_philo < 1 || table->nbr_philo > 200)
		ft_print_error(BAD_IMPUT);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->nb_must_eat = ft_atol(argv[5]);
	else
		table->nb_must_eat = -1;
	table->finished = 0;
	table->dead = 0;
	table->mutex_table = malloc(sizeof(pthread_mutex_t));
	if (!table->mutex_table)
		ft_print_error(MALLOC_FAIL);
	if ((pthread_mutex_init(table->mutex_table, NULL)) != 0)
		ft_print_error(MUTEX);
	ft_init_forks(table);
}

/*
for debug:
	philo[i].indice[0] = i;//erase
	philo[i].indice[1] = 0;//erase
	philo[i].indice[0] = i;//erase
	philo[i].indice[1] = i + 1;//erase
	printf("ESTA ES LA IIII:%d\n", philo[i].indice[0]);//erase
	printf("ESTA ES LA IIII:%d\n", philo[i].indice[1]);//erase
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

int	main(int argc, char **argv)
{
	atexit(ft_leaks);
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
