/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:09:57 by gita              #+#    #+#             */
/*   Updated: 2025/11/17 22:48:42 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_PHILOS_H
# define HEADER_PHILOS_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data
{
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	pthread_t		*philo_threads;
	t_philo			*philo_queue;
	pthread_mutex_t	*forks;
	time_t			start_time_of_prog;		
}	t_data;

typedef struct s_philo
{
	pthread_t	thread_no;
	size_t		id;
	int			alr_ate;
	size_t		ate_enough_times;
	int			alr_slept;
	int			starved_to_death;
	t_data		*data;
}	t_philo;


int		validate_args(int ac, char **av);
int		ft_atoi(char *str);
void	ft_atoi_beginning(char *str, size_t *i, int *sign);
int		print_msg_n_return_value(char *msg, int value);
void	cleanup_data(t_data *data);

int		register_data(int ac, char **av, t_data *supervisor);
void	basic_data(int ac, char **av, t_data *data);
int		init_threads(t_data *supervisor);
int		join_threads(t_data *data, int quantity);
void	*philo_prog(void *arg);
void	*supervise_prog(void *arg);

time_t	simplified_time();
#endif