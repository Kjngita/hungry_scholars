/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_philo.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:09:57 by gita              #+#    #+#             */
/*   Updated: 2025/11/25 22:13:27 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_PHILOS_H
# define HEADER_PHILOS_H

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
	size_t			max_meals;
	size_t			happy_philos;
	pthread_t		*philo_threads;
	t_philo			*philo_queue;
	pthread_mutex_t	*forks;
	uint64_t		start_time_of_prog;
	int				stop_prog;
	pthread_mutex_t	data_protection;
}	t_data;

typedef struct s_philo
{
	// pthread_t		thread_no;
	size_t			id;
	int				is_eating;
	size_t			meals_eaten;
	uint64_t		last_bite;
	// uint64_t		last_nap;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	personal_bodyguard;
	t_data			*data;
}	t_philo;


int			validate_args(int ac, char **av);
int			ft_atoi(char *str);
void		ft_atoi_beginning(char *str, size_t *i, int *sign);
int			print_msg_n_return_value(char *msg, int value);
void		cleanup_data(t_data *data);

int			register_data(int ac, char **av, t_data *supervisor);
void		basic_data(int ac, char **av, t_data *data);
void		assign_forks(t_data *data, size_t i);
int			init_threads(t_data *supervisor);
int			join_threads(t_data *data, size_t quantity);

void		*philo_prog(void *arg);
void		think_deeply(t_philo *philo);

void		*supervise_prog(void *arg);
void		check_if_starved(t_data *data);
void		check_if_all_full(t_data *data);

uint64_t	simplified_time();
void		announcement_to_screen(t_data *data, t_philo *philo, char *activity);
void		eat_cleanly(t_philo *philo);
void		sleep_soundly(t_philo *philo);
void		think_boldly(t_philo *philo);
#endif