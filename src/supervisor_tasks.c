/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_tasks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:02:33 by gita              #+#    #+#             */
/*   Updated: 2025/11/19 22:56:37 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

void	*supervise_prog(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	printf("\nCreated superviser thread\n");
	// printf("Time to die=%i eat=%i sleep=%i\n", data->time_to_die, data->time_to_eat, data->time_to_sleep);
	// printf("Number of meals = %i\n", data->number_of_meals);
	while (!data->stop_prog)
	{
		check_if_starved(data);
		check_if_all_full(data);
	}
	return (NULL);
}

void	check_if_starved(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->head_count)
	{
		if (!data->philo_queue[i].is_eating &&
			(data->philo_queue[i].data->hunger_endurance <
			simplified_time() - data->philo_queue[i].last_bite))
		{
			data->stop_prog = 1;
			//join threads, clear data, bye;
		}
		i++;
	}
}

void	check_if_all_full(t_data *data)
{
	size_t	i;

	i = 0;
	data->happy_philos = 0;
	while (i < data->head_count)
	{
		if (data->philo_queue[i].meals_eaten >= data->max_meals)
			data->happy_philos++;
		i++;
	}
	if (data->happy_philos == data->head_count)
	{
		data->stop_prog = 1;
		//join threads, clear data, bye;
	}
}
