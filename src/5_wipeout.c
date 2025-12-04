/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_wipeout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 23:05:21 by gita              #+#    #+#             */
/*   Updated: 2025/12/04 23:55:21 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	print_err_n_return_value(char *msg, int value)
{
	if (msg)
		printf("%s\n", msg);
	return (value);
}

int	dump_meal_mutex(t_data *data, size_t quantity)
{
	size_t i;

	i = 0;
	if (!data || !data->philo_queue)
		return (-1);
	while (i < quantity)
	{
		if (pthread_mutex_destroy(&data->philo_queue[i].meal_info_access) != 0)
		{
			printf("Destroy meal info mutex failed midway\n");
			return (-1);
		}
		i++;
	}
	if (i < data->head_count)
	{
		printf("Meal mutex init failed\n");
		return (-1);
	}
	return (0);
}

void	cleanup_data(t_data *data)
{
	if (!data)
		return ;
	if (data->philo_threads)
	{
		free (data->philo_threads);
		data->philo_threads = NULL;
	}
	if (data->philo_queue)
	{
		free (data->philo_queue);
		data->philo_queue = NULL;
	}
	if (data->forks)
	{
		dump_forks(&data, data->head_count);
	}
	pthread_mutex_destroy(&data->printer_access);
	pthread_mutex_destroy(&data->termination_access);
}

void	dump_forks(t_data **data, size_t quantity)
{
	size_t	i;

	i = 0;
	while (i < quantity)
	{
		pthread_mutex_destroy(&(*data)->forks[i]);
		i++;
	}
	free ((*data)->forks);
	(*data)->forks = NULL;
}
