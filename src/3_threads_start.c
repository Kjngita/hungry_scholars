/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_threads_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:45:48 by gita              #+#    #+#             */
/*   Updated: 2025/12/05 17:59:50 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	init_threads(t_data *data, pthread_t *supervisor)
{
	size_t		i;

	i = 0;
	while (i < data->head_count)
	{
		if (pthread_create(&data->philo_threads[i], NULL, &philo_prog,
				&data->philo_queue[i]) != 0)
		{
			pthread_mutex_lock(&data->termination_access);
			data->terminate_prog = 1;
			pthread_mutex_unlock(&data->termination_access);
			return (join_threads(data, i));
		}
		i++;
	}
	if (pthread_create(supervisor, NULL, &supervise_prog, data) != 0)
	{
		join_threads(data, data->head_count);
		supervisor_creation_fail(data);
		return (-1);
	}
	pthread_mutex_lock(&data->termination_access);
	data->terminate_prog = 0;
	pthread_mutex_unlock(&data->termination_access);
	return (0);
}

int	join_threads(t_data *data, size_t quantity)
{
	size_t	i;

	i = 0;
	while (i < quantity)
	{
		if (pthread_join(data->philo_threads[i], NULL) != 0)
		{
			pthread_mutex_lock(&data->printer_access);
			printf("Thread join failed");
			pthread_mutex_unlock(&data->printer_access);
			return (-1);
		}
		i++;
	}
	if (i < data->head_count)
	{
		pthread_mutex_lock(&data->printer_access);
		printf("Threads creation failed midway");
		pthread_mutex_unlock(&data->printer_access);
		return (-1);
	}
	return (0);
}

void	supervisor_creation_fail(t_data *data)
{
	pthread_mutex_lock(&data->termination_access);
	data->terminate_prog = 1;
	pthread_mutex_unlock(&data->termination_access);
	pthread_mutex_lock(&data->printer_access);
	printf("S-thread creation failed");
	pthread_mutex_unlock(&data->printer_access);
}

void	announcement_to_screen(t_data *data, t_philo *philo, char *activity)
{
	uint64_t	timestamp_in_milsec;

	pthread_mutex_lock(&data->termination_access);
	if (data->terminate_prog == 1)
	{
		pthread_mutex_unlock(&data->termination_access);
		return ;
	}
	pthread_mutex_unlock(&data->termination_access);
	pthread_mutex_lock(&data->printer_access);
	timestamp_in_milsec = simplified_time() - data->start_time_of_prog;
	printf("%lu %zu %s\n", timestamp_in_milsec, philo->id, activity);
	pthread_mutex_unlock(&data->printer_access);
}
