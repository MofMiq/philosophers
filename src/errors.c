/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:46:17 by marirodr          #+#    #+#             */
/*   Updated: 2023/07/26 13:58:51 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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
	else if (error == FORK)
		printf("Error! Failed to create forks\n");
	else if (error == THREAD)
		printf("Error! Failed to create threads\n");
	exit(1);
}
