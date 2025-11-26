/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:45:48 by gita              #+#    #+#             */
/*   Updated: 2025/11/26 18:21:01 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	init_threads(t_data *data)
{
	size_t		i;
	pthread_t	supervisor;

	i = 0;
	while (i < data->head_count)
	{
		data->philo_queue[i].id = i + 1;
		if (pthread_create(&data->philo_threads[i], NULL, &philo_prog,
				&data->philo_queue[i]) != 0)
		{
			pthread_mutex_lock(&data->data_protection);
			data->stop_prog = 1;
			pthread_mutex_unlock(&data->data_protection);
			return (join_threads(data, i));
		}
		i++;
	}
	data->start_time_of_prog = simplified_time();
	if (pthread_create(&supervisor, NULL, &supervise_prog, data) != 0)
		return (print_err_n_return_value("S-thread creation failed", -1));
	if (pthread_join(supervisor, NULL) != 0)
		return (print_err_n_return_value("S-thread join failed", -1));
	if (join_threads(data, data->head_count) == -1)
		return (-1);
	return (0);
}

int	join_threads(t_data *data, size_t quantity)
{
	size_t	i;

	i = 0;
	while (i < quantity)
	{
		if (pthread_join(data->philo_threads[i], NULL) != 0)
			return (print_err_n_return_value("Thread join failed", -1));
		i++;
	}
	if (i < data->head_count)
		return (print_err_n_return_value("Threads creation failed midway", -1));
	return (0);
}

uint64_t	simplified_time(void)
{
	struct timeval	this_moment;

	gettimeofday(&this_moment, NULL);
	return (((this_moment.tv_sec * 1000) + (this_moment.tv_usec / 1000)));
}

void	announcement_to_screen(t_data *data, t_philo *philo, char *activity)
{
	uint64_t	timestamp_in_millisec;

	pthread_mutex_lock(&data->data_protection);
	if (activity == NULL)
	{
		data->stop_prog = 1;
		timestamp_in_millisec = simplified_time() - data->start_time_of_prog;
		printf("%lu %zu %s\n", timestamp_in_millisec, philo->id, "died");
	}
	if (!data->stop_prog)
	{
		timestamp_in_millisec = simplified_time() - data->start_time_of_prog;
		printf("%lu %zu %s\n", timestamp_in_millisec, philo->id, activity);
	}
	pthread_mutex_unlock(&data->data_protection);
}
