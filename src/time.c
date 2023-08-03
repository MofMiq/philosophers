/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:18:39 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/03 11:48:52 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long long	ft_get_system_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*
debug
long long system;
long long now;
system = ft_get_system_time();
printf("%lld system time\n", system);
now = ft_get_system_time() - system;
printf("%lld now time\n", now);
printf("%lld putito tiempito\n", table->time_start);*/

long long	ft_current_time(t_table *table)
{
	return (ft_get_system_time() - table->time_start);
}
