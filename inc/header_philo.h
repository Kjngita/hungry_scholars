/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:38:58 by gita              #+#    #+#             */
/*   Updated: 2025/12/06 16:24:41 by gita             ###   ########.fr       */
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

typedef struct s_philo	t_philo;
typedef struct s_data
{
	size_t			head_count;
	uint64_t		hunger_endurance;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	size_t			forced_meals;
	pthread_t		*philo_threads;
	t_philo			*philo_queue;
	uint64_t		start_time_of_prog;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer_access;
	pthread_mutex_t	termination_access;
	int				terminate_prog;
}	t_data;

typedef struct s_philo
{
	size_t			id;
	int				is_eating;
	size_t			meals_eaten;
	uint64_t		last_bite;
	pthread_mutex_t	meal_info_access;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

int			validate_args(int ac, char **av);
int			philo_atoi(char *str);
void		philo_atoi_beginning(char *str, size_t *i, int *sign);

int			register_data(int ac, char **av, t_data *supervisor);
void		basic_data(int ac, char **av, t_data *data);
int			reserve_space_for_stuff(t_data *data);
void		assign_forks(t_data *data, size_t i);
uint64_t	simplified_time(void);

int			init_threads(t_data *data, pthread_t *supervisor);
int			join_threads(t_data *data, size_t quantity);
void		supervisor_creation_fail(t_data *data);
void		announcement_to_screen(t_data *data, t_philo *philo,
				char *activity);

void		*philo_prog(void *arg);
int			wait_all_threads(t_data *data);
void		lonely_philo(t_philo *philo);
void		eat_cleanly(t_philo *philo);
void		sleep_soundly(t_philo *philo);
void		think_boldly(t_philo *philo);

void		*supervise_prog(void *arg);
int			check_if_stopped(t_data *data);
int			check_if_starved(t_data *data);
void		death_notice(t_philo *philo);
int			check_if_all_full(t_data *data);

int			wait_threads_to_finish(t_data *data, pthread_t *supervisor);
int			print_err_n_return_value(char *msg, int value);
void		cleanup_data(t_data *data);
void		dump_forks(t_data **data, size_t quantity);
int			dump_meal_mutex(t_data *data, size_t quantity);

#endif