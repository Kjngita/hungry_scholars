/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_register.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:34:43 by gita              #+#    #+#             */
/*   Updated: 2025/12/03 18:33:30 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

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
	i = 0;
	while (i < data->head_count)
	{
		memset(&data->philo_queue[i], 0, sizeof(t_philo));
		data->philo_queue[i].id = i + 1;
		data->philo_queue[i].data = data;
		data->philo_queue[i].last_bite = data->start_time_of_prog;
		assign_forks(data, i);
		if (pthread_mutex_init(&data->philo_queue[i].meal_info_access, NULL))
			return (print_err_n_return_value("Meal mutex init failed", -1));
		i++;
	}
	return (0);
}

void	basic_data(int ac, char **av, t_data *data)
{
	data->head_count = ft_atoi(av[1]);
	data->hunger_endurance = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->forced_meals = ft_atoi(av[5]);
}

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
