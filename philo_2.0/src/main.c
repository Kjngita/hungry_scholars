/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:07 by gita              #+#    #+#             */
/*   Updated: 2025/12/02 23:42:01 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	supervisor;

	if (!(ac == 5 || ac == 6))
		return (print_err_n_return_value("Incorrect number of args", 1));
	if (validate_args(ac, av) == -1)
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (register_data(ac, av, &data) == -1)
	{
		cleanup_data(&data);
		return (1);
	}
	if (init_threads(&data, &supervisor) == -1)
	{
		cleanup_data(&data);
		return (1);
	}
	if (pthread_join(supervisor, NULL) != 0)
		return (print_err_n_return_value("S-thread join failed", -1));
	if (join_threads(&data, data.head_count) == -1)
		return (-1);
	cleanup_data(&data);
	return (0);
}

int	print_err_n_return_value(char *msg, int value)
{
	if (msg)
		printf("%s\n", msg);
	return (value);
}

void	cleanup_data(t_data *data)
{
	// size_t	i;

	if (!data)
		return ;
	if (data->philo_threads)
	{
		free (data->philo_threads);
		data->philo_threads = NULL;
	}
	if (data->philo_queue)
	{
		// i = 0;
		// while (i < data->head_count)
		// {
		// 	pthread_mutex_destroy(&data->philo_queue[i].personal_bodyguard);
		// 	i++;
		// }
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
