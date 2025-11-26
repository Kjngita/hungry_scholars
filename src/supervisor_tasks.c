/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_tasks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:02:33 by gita              #+#    #+#             */
/*   Updated: 2025/11/26 17:42:47 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

void	*supervise_prog(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->stop_prog)
	{
		if (check_if_starved(data) == 1)
			break ;
		if (data->max_meals > 0 && check_if_all_full(data) == 1)
			break ;
		usleep(100);
	}
	return (NULL);
}

int	check_if_starved(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->head_count)
	{
		if (!data->philo_queue[i].is_eating
			&& (data->philo_queue[i].data->hunger_endurance
				< simplified_time() - data->philo_queue[i].last_bite))
		{
			pthread_mutex_lock(&data->data_protection);
			data->stop_prog = 1;
			pthread_mutex_unlock(&data->data_protection);
			announcement_to_screen(data, &data->philo_queue[i], NULL);
			return (1);
		}
		i++;
		usleep (100);
	}
	return (0);
}

int	check_if_all_full(t_data *data)
{
	size_t	i;

	i = 0;
	data->happy_philos = 0;
	while (i < data->head_count)
	{
		if (data->philo_queue[i].meals_eaten >= data->max_meals)
			data->happy_philos++;
		i++;
		usleep (100);
	}
	if (data->happy_philos == data->head_count)
	{
		pthread_mutex_lock(&data->data_protection);
		data->stop_prog = 1;
		pthread_mutex_unlock(&data->data_protection);
		return (1);
	}
	return (0);
}
