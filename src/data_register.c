/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_register.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:34:43 by gita              #+#    #+#             */
/*   Updated: 2025/11/25 18:35:08 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	register_data(int ac, char **av, t_data *data)
{
	size_t	i;

	basic_data(ac, av, data);
	data->philo_threads = malloc(sizeof(pthread_t) * data->head_count);
	if (!data->philo_threads)
		return (print_msg_n_return_value("Malloc failed for philo thread", -1));
	data->philo_queue = malloc(sizeof(t_philo) * data->head_count);
	if (!data->philo_queue)
		return (print_msg_n_return_value("Malloc failed for philo queue", -1));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->head_count);
	if (!data->forks)
		return (print_msg_n_return_value("Malloc failed for forks", -1));
	i = 0;
	while (i < data->head_count)
	{
		memset(&data->philo_queue[i], 0, sizeof(t_philo));
		data->philo_queue[i].data = data;
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (print_msg_n_return_value("Fork pthread init failed", -1));
		assign_forks(data, i);
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
		data->max_meals = ft_atoi(av[5]);
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
