/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:21:57 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/04 11:32:21 by marirodr         ###   ########.fr       */
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
# include <sys/types.h>

# define YELLOW "\033[0;93m"
# define BLUE "\033[0;96m"
# define PURPLE "\033[0;95m"
# define PINK "\033[0;91m"
# define RED "\033[0;31m"
# define END "\033[0m"

# define WRONG_NBR		1
# define BAD_IMPUT		2
# define EXCED_LIMT		3
# define MALLOC_FAIL	4
# define MUTEX			5
# define THREAD			6

typedef struct s_table
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				finished;
	int				dead;
	long long		time_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex_table;
}	t_table;

//int indice[2]; //for debuging forks

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				id;
	int				cur_eat;
	long long		last_eat;
	t_table			*table;
}	t_philo;

//philosophers.c (main)
void		ft_init_forks(t_table *table);
void		ft_init_table(int argc, char **argv, t_table *table);
void		ft_init_philosophers(t_philo *philo, t_table *table);
//debug
void		ft_leaks(void);

//print_n_free.c
void		ft_print_error(int error);
void		ft_print_msg(t_philo *philo, int i);
void		ft_free_forks_mutex(t_table *table);
void		ft_free_all(t_philo *philo, t_table *table);

//check_arg.c
int			ft_check_arg(char **argv);
int			ft_is_number(char *str);
int			ft_number_limit(char *str);
long		ft_atol(char *str);

//time.c
long long	ft_get_system_time(void);
long long	ft_current_time(t_table *table);

//loop.c
int			ft_must_stop(t_table *table);
int			ft_is_dead(t_philo *philo);
void		ft_infinite_loop(t_philo *philo, t_table *table);
void		*ft_rutine(void *arg);
void		ft_create_thread(t_philo *philo, t_table *table);

//rutine.c
void		*ft_one_philo(void *arg);
void		*ft_eat(t_philo *philo);
void		*ft_sleep(t_philo *philo);
void		*ft_think(t_philo *philo);
void		ft_right_or_left_handed(t_philo *philo);

#endif