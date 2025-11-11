/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:09:57 by gita              #+#    #+#             */
/*   Updated: 2025/11/11 22:40:21 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_PHILOS_H
# define HEADER_PHILOS_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

typedef struct s_philo	t_philo;
typedef struct s_data
{
	int			nbr_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meals;
	pthread_t	*philo_threads;
	t_philo		*philo_queue;
}	t_data;

typedef struct s_philo
{
	pthread_t	thread_no;
	size_t		id;
	int			alr_ate;
	size_t		ate_enough_times;
	int			alr_slept;
	t_data		*data;
}	t_philo;


int		validate_args(int ac, char **av);
int		ft_atoi(char *str);
int		print_msg_n_return_value(char *msg, int value);
void	cleanup_data(t_data *data);

int		register_data(int ac, char **av, t_data *supervisor);
int		init_threads(t_data *supervisor);
void	*start_of_prog(void *arg);
void	*supervise_prog(void *arg);

#endif