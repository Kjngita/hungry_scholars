/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_data_register.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:34:43 by gita              #+#    #+#             */
/*   Updated: 2025/12/05 17:55:47 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

/*
For t_data struct:
- Fill with info from user input, malloc necessary spaces, initialize 2 mutexes
used for printing messages and changing terminate_prog value (now set as -1 to
indicate not all threads have been created), set start time by helper function

For each t_philo struct:
- Give them id number, pointer to the same t_data struct, time of last meal,
pointers to fork mutexes, and initialize mutex for updating/checking last meal
and number of meals

Return: 0 on success, -1 on errors
*/
int	register_data(int ac, char **av, t_data *data)
{
	size_t	i;

	basic_data(ac, av, data);
	if (reserve_space_for_stuff(data) == -1)
		return (-1);
	if (pthread_mutex_init(&data->printer_access, NULL) != 0)
		return (print_err_n_return_value("Print mutex init failed", -1));
	if (pthread_mutex_init(&data->termination_access, NULL) != 0)
		return (print_err_n_return_value("Stop mutex init failed", -1));
	data->start_time_of_prog = simplified_time();
	data->terminate_prog = -1;
	i = 0;
	while (i < data->head_count)
	{
		memset(&data->philo_queue[i], 0, sizeof(t_philo));
		data->philo_queue[i].id = i + 1;
		data->philo_queue[i].data = data;
		data->philo_queue[i].last_bite = data->start_time_of_prog;
		assign_forks(data, i);
		if (pthread_mutex_init(&data->philo_queue[i].meal_info_access, NULL))
			return (dump_meal_mutex(data, i));
		i++;
	}
	return (0);
}

/*
Set number of philos, time to die, time to eat, time to sleep,
and possible number of required meals in t_data struct
(helper function of register_data())
*/
void	basic_data(int ac, char **av, t_data *data)
{
	data->head_count = philo_atoi(av[1]);
	data->hunger_endurance = philo_atoi(av[2]);
	data->time_to_eat = philo_atoi(av[3]);
	data->time_to_sleep = philo_atoi(av[4]);
	if (ac == 6)
		data->forced_meals = philo_atoi(av[5]);
}

/*
Malloc the memory for the array of pthread_t (used when creating philo threads),
array of t_philo structs, array of fork mutexes then initiate the mutexes
(helper function of register_data())

Return: 0 on success, -1 on errors
*/
int	reserve_space_for_stuff(t_data *data)
{
	size_t	i;

	data->philo_threads = malloc(sizeof(pthread_t) * data->head_count);
	if (!data->philo_threads)
		return (print_err_n_return_value("Malloc failed for philo thread", -1));
	data->philo_queue = malloc(sizeof(t_philo) * data->head_count);
	if (!data->philo_queue)
		return (print_err_n_return_value("Malloc failed for philo queue", -1));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->head_count);
	if (!data->forks)
		return (print_err_n_return_value("Malloc failed for forks", -1));
	i = 0;
	while (i < data->head_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			dump_forks(&data, i);
			return (print_err_n_return_value("Fork mutexes init failed", -1));
		}
		i++;
	}
	return (0);
}

/*
Give instruction for each philo where to claim left and right fork mutexes 
from the array of fork mutexes
(helper function of register_data())
*/
void	assign_forks(t_data *data, size_t i)
{
	data->philo_queue[i].left_fork = &data->forks[i];
	if (data->head_count > 1)
	{
		if (i + 1 == data->head_count)
			data->philo_queue[i].right_fork = &data->forks[0];
		else
			data->philo_queue[i].right_fork = &data->forks[i + 1];
	}
}

/*
Convert the info of time stored in the timeval struct to an integer

Return: The time in milisecond
*/
uint64_t	simplified_time(void)
{
	struct timeval	this_moment;

	gettimeofday(&this_moment, NULL);
	return (((this_moment.tv_sec * 1000) + (this_moment.tv_usec / 1000)));
}
