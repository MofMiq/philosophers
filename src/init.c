/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:33:17 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/01 17:22:04 by marirodr         ###   ########.fr       */
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
			//own free function & detroy mutex
			ft_print_error(FORK);
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
	table->dead = 0;
	table->mutex_table = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->mutex_table, NULL);
	ft_init_forks(table);
}

void	ft_init_philosophers(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].cur_eat = 0;
		philo[i].last_eat = 0;
		philo[i].dead_time = 0;
		philo[i].table = table;
		if (philo[i].id == table->nbr_philo)
		{
			philo[i].l_fork = &table->forks[i];
			philo[i].r_fork = &table->forks[0];
			philo[i].indice[0] = i;//erase
			philo[i].indice[1] = 0;//erase
			printf("ULTIMO:%d\n", i);//erase
		}
		else
		{
			philo[i].l_fork = &table->forks[i];
			philo[i].r_fork = &table->forks[i + 1];
			philo[i].indice[0] = i;//erase
			philo[i].indice[1] = i + 1;//erase
			printf("ESTA ES LA IIII:%d\n", philo->indice[0]);//erase
			printf("ESTA ES LA IIII:%d\n", philo->indice[1]);//erase
		}
		i++;
	}
}
