/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:38:58 by gita              #+#    #+#             */
/*   Updated: 2025/11/29 23:10:50 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_PHILO_H
# define HEADER_PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <stdint.h>
# include <sys/time.h>
# include <stdatomic.h>

typedef struct s_philo	t_philo;
typedef struct s_data
{
	size_t			head_count;
	uint64_t		hunger_endurance;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	size_t			max_meals;
	size_t			happy_philos;
	pthread_t		*philo_threads;
	t_philo			*philo_queue;
	pthread_mutex_t	*forks;
	uint64_t		start_time_of_prog;
	atomic_int		stop_prog;
	// pthread_mutex_t	data_protection;
}	t_data;

typedef struct s_philo
{
	size_t			id;
	int				is_eating;
	size_t			meals_eaten;
	uint64_t		last_bite;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	personal_bodyguard;
	t_data			*data;
}	t_philo;

int			validate_args(int ac, char **av);
int			ft_atoi(char *str);
void		ft_atoi_beginning(char *str, size_t *i, int *sign);

int			register_data(int ac, char **av, t_data *supervisor);
void		basic_data(int ac, char **av, t_data *data);
int			reserve_space_for_stuff(t_data *data);
void		assign_forks(t_data *data, size_t i);
int			init_threads(t_data *supervisor);
int			lonely_philo(t_data *data);
int			join_threads(t_data *data, size_t quantity);

void		*philo_prog(void *arg);
void		eat_cleanly(t_philo *philo);
void		sleep_soundly(t_philo *philo);
void		think_boldly(t_philo *philo);

void		*supervise_prog(void *arg);
int			check_if_starved(t_data *data);
int			check_if_all_full(t_data *data);

int			print_err_n_return_value(char *msg, int value);
void		cleanup_data(t_data *data);
uint64_t	simplified_time(void);
void		announcement_to_screen(t_data *data, t_philo *philo,
				char *activity);

#endif