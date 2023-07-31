/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:21:57 by marirodr          #+#    #+#             */
/*   Updated: 2023/07/31 12:42:26 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# define YELLOW "\033[0;93m"
# define BLUE "\033[0;96m"
# define PURPLE "\033[0;95m"
# define PINK "\033[0;91m"
# define END "\033[0m"

# define WRONG_NBR		1
# define BAD_IMPUT		2
# define EXCED_LIMT		3
# define MALLOC_FAIL	4
# define FORK			5
# define THREAD			6

typedef struct s_table
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				dead;
	long long		time_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*table_mutex;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	int				r_fork;
	int				l_fork;
	int				id;
	int				status;
	int				cur_eat;
	int				last_eat;
	int				dead_time;
	t_table			*table;
}	t_philo;

//errors.c
void	ft_print_error(int error);
//void	ft_free_table(t_table *table);

//check_arg.c
int		ft_check_arg(char **argv);
int		ft_is_number(char *str);
int		ft_number_limit(char *str);
long	ft_atol(char *str);

//main
void	ft_init_table(int argc, char **argv, t_table *table);
void	ft_init_forks(t_table *table);

//time.c
long long	ft_get_system_time(void);
long long	ft_current_time(t_table *table);

#endif