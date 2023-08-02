/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:42:59 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/01 15:30:19 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_infinite_loop(t_philo *philo, t_table *table)
{
	(void)philo;
	(void)table;
	while (1)
	{
		usleep(10);
	}
}

void	*ft_testing(void *arg)
{
	long long	i;
	t_philo		*philo;

	philo = (t_philo *)arg;
	i = ft_current_time(philo->table);
	if (philo->table->nb_must_eat == 0)
		return (NULL);
	if (philo->table->time_to_die == 0)
		return (NULL);
	//alguna comprobacion mas?
	while (i < 0)
	{
		i = ft_current_time(philo->table);
		philo->last_eat = i;
		usleep(1);
	}
	while (philo->table->dead == 0) // como me organizo la comprobacion de muerte?
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_create_thread(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_philo == 1)
	{
		table->time_start = ft_get_system_time();
		if ((pthread_create(&philo[i].thread, NULL, ft_one_philo, &philo[i])) != 0)
			ft_print_error(THREAD);
		ft_free_all(philo, table);
	}
	else
	{
		table->time_start = ft_get_system_time() + table->nbr_philo * 20;
		//tiempo guay
		while (i < table->nbr_philo)
		{
			if ((pthread_create(&philo[i].thread, NULL, ft_testing, &philo[i])) != 0)
				ft_print_error(THREAD);
			i++;
		}
		ft_infinite_loop(philo, table);
		//pthread_join(philo[i].thread, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		ft_print_error(WRONG_NBR);
	if (!ft_check_arg(argv))
		printf("ok\n");
	ft_init_table(argc, argv, &table);
	philo = malloc(sizeof(t_philo) * table.nbr_philo);
	if (!philo)
		ft_print_error(MALLOC_FAIL);
	ft_init_philosophers(philo, &table);
	ft_create_thread(philo, &table);
	//teoria
	/*while (table.dead == 0)
	{
	}*/
}
