/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:45:50 by marirodr          #+#    #+#             */
/*   Updated: 2023/07/26 12:45:53 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_check_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_is_number(argv[i]))
			ft_print_error(BAD_IMPUT);
		if (ft_number_limit(argv[i]))
			ft_print_error(EXCED_LIMT);
		i++;
	}
	return (0);
}

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_number_limit(char *str)
{
	long	nb;

	nb = ft_atol(str);
	if (nb >= 0 && nb <= INT_MAX)
		return (0);
	return (1);
}

long	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}
