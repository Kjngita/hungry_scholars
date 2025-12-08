/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_wipeout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 23:05:21 by gita              #+#    #+#             */
/*   Updated: 2025/12/08 23:03:13 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

/*
Simple error printing and return passed value
*/
int	print_err_n_return_value(char *msg, int value)
{
	if (msg)
		printf("%s\n", msg);
	return (value);
}

/*
- Destroy mutex for accessing meal info in as many t_philo structs as the number
passed to the function. If fail, stop and display a message on screen
- If the number passed to the function is smaller than the number of philos,
it indicates that the mutex initializing loop in data register had a problem,
hence return -1

Return: 0 on success, -1 on errors
*/
int	dump_meal_mutex(t_data *data, size_t quantity)
{
	size_t	i;

	i = 0;
	if (!data || !data->philo_queue)
		return (print_err_n_return_value("Could not retrieve data", -1));
	while (i < quantity)
	{
		if (pthread_mutex_destroy(&data->philo_queue[i].meal_info_access) != 0)
		{
			return (print_err_n_return_value("Destroy meal info mutex failed "
					"midway", -1));
		}
		i++;
	}
	if (i < data->head_count)
	{
		return (print_err_n_return_value("Meal mutex init failed", -1));
	}
	return (0);
}

/*
Free and assign as NULL all malloced pointers. Destroy the mutexes for printing
and changing terminate_prog value.
*/
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
	if (pthread_mutex_destroy(&data->printer_access) != 0
		|| pthread_mutex_destroy(&data->termination_access) != 0)
		printf("Error destroying mutex\n");
}

/*
Destroy the asked quantity of fork mutexes. Free and assign as NULL the pointer
to the array of fork mutexes.
*/
void	dump_forks(t_data **data, size_t quantity)
{
	size_t	i;

	i = 0;
	while (i < quantity)
	{
		if (pthread_mutex_destroy(&(*data)->forks[i]) != 0)
			printf("Error destroying fork mutex\n");
		i++;
	}
	free ((*data)->forks);
	(*data)->forks = NULL;
}
