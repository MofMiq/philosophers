/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:18:39 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/08 18:22:32 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*This function retrieves the operating system's time values. To begin with, we
call gettimeofday, which provides us with the count of seconds (tv_sec) and
microseconds (tv_usec) that have transpired since 01/01/1970 – a date selected
for technical considerations. Subsequently, we convert each value to
milliseconds as stipulated by the project's requirements.*/

long long	ft_get_system_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*This function is the one responsible for "setting" the program's starting time
to 0 through a simple subtraction. This way, we will be able to clearly observe
in the output whether the philosophers adhere to the specified timings.*/

long long	ft_current_time(t_table *table)
{
	long long	time;

	//pthread_mutex_lock(&table->mutex_time);
	time = ft_get_system_time() - table->time_start;
	//pthread_mutex_unlock(&table->mutex_time);
	return (time);
}
