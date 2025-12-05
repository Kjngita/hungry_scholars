/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_supervisor_tasks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:02:33 by gita              #+#    #+#             */
/*   Updated: 2025/12/05 18:00:32 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

void	*supervise_prog(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_if_stopped(data) == 1)
			break ;
		if (check_if_starved(data) == 1)
			break ;
		if (data->forced_meals > 0 && check_if_all_full(data) == 1)
			break ;
		usleep(100);
	}
	return (NULL);
}

int	check_if_stopped(t_data *data)
{
	int	gotta_stop;

	pthread_mutex_lock(&data->termination_access);
	gotta_stop = data->terminate_prog;
	pthread_mutex_unlock(&data->termination_access);
	return (gotta_stop);
}

int	check_if_starved(t_data *data)
{
	size_t		i;
	uint64_t	last_bite;

	i = 0;
	while (i < data->head_count)
	{
		pthread_mutex_lock(&data->philo_queue[i].meal_info_access);
		last_bite = data->philo_queue[i].last_bite;
		pthread_mutex_unlock(&data->philo_queue[i].meal_info_access);
		if (data->hunger_endurance < simplified_time() - last_bite)
		{
			pthread_mutex_lock(&data->termination_access);
			data->terminate_prog = 1;
			pthread_mutex_unlock(&data->termination_access);
			death_notice(&data->philo_queue[i]);
			return (1);
		}
		i++;
		usleep (100);
	}
	return (0);
}

void	death_notice(t_philo *philo)
{
	uint64_t	timestamp_in_milsec;

	pthread_mutex_lock(&philo->data->printer_access);
	timestamp_in_milsec = simplified_time() - philo->data->start_time_of_prog;
	printf("%lu %zu %s\n", timestamp_in_milsec, philo->id, "died");
	pthread_mutex_unlock(&philo->data->printer_access);
}

int	check_if_all_full(t_data *data)
{
	size_t	i;
	size_t	happy_philos;

	i = 0;
	happy_philos = 0;
	while (i < data->head_count)
	{
		pthread_mutex_lock(&data->philo_queue[i].meal_info_access);
		if (data->philo_queue[i].meals_eaten >= data->forced_meals)
			happy_philos++;
		pthread_mutex_unlock(&data->philo_queue[i].meal_info_access);
		i++;
		usleep (100);
	}
	if (happy_philos == data->head_count)
	{
		pthread_mutex_lock(&data->termination_access);
		data->terminate_prog = 1;
		pthread_mutex_unlock(&data->termination_access);
		return (1);
	}
	return (0);
}
