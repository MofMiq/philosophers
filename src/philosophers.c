/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:42:59 by marirodr          #+#    #+#             */
/*   Updated: 2023/07/31 13:14:11 by marirodr         ###   ########.fr       */
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
		printf("[%d] fork created\n", i); //testing
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
		//ft_left_n_right(philo[i]);
		i++;
	}
}

void	*ft_testing(void *arg)
{
	long long		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	i = ft_current_time(philo->table);
	printf("time now is %lld\n", i);
	//printf("[%lld] [%d] TIEMPO DEL SISTEMA!!!\n", philo->table->time_start, philo->id);
	while (i < 0)
	{
		i = ft_current_time(philo->table);
		//printf("[%lld] [%d] Tiempo de inicio!!!\n", i, philo->id);
	}
	//printf("[%lld] [%d] Tiempo antes de bucle!!!\n", i, philo->id);
	while (1)
	{
		//printf("[%lld] [%d] holis!!!\n", i, philo->id);
	}
	return (NULL);
}

void	ft_create_thread(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	table->time_start = ft_get_system_time() + table->nbr_philo * 20;
	if (table->nbr_philo == 1)
	{
		table->time_start = ft_get_system_time();
		if ((pthread_create(&philo[i].thread, NULL, ft_testing, &philo[i])) != 0)
			ft_print_error(THREAD);
		printf("[%d] philo created\n", philo->id);
	}
	else
	{
		while (i < table->nbr_philo)
		{
		//	philo->thread = malloc(sizeof(pthread_t));
			if ((pthread_create(&philo[i].thread, NULL, (void *)ft_testing, &philo[i])) != 0)
				ft_print_error(THREAD);
			//pthread_join(philo[i].thread, NULL);
			//printf("[%d] philo created\n", philo[i].id);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		ft_print_error(WRONG_NBR);
	if (!ft_check_arg(argv))
		printf("args are OK!!\nnow next step\n");
	ft_init_table(argc, argv, &table);
	philo = malloc(sizeof(t_philo) * table.nbr_philo);
	if (!philo)
		ft_print_error(MALLOC_FAIL);
	ft_init_philosophers(philo, &table);
	ft_create_thread(philo, &table);
}
