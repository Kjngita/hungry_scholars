/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:07 by gita              #+#    #+#             */
/*   Updated: 2025/11/19 22:52:52 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!(ac == 5 || ac == 6))
		return (print_msg_n_return_value("Incorrect number of arguments", 1));
	if (validate_args(ac, av) == -1)
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (register_data(ac, av, &data) == -1)
	{
		cleanup_data(&data);
		return (1);
	}
	if (init_threads(&data) == -1)
	{
		cleanup_data(&data);
		return (1);	
	}printf("Back to main\n");
	cleanup_data(&data);
	return (0);
}

int	print_msg_n_return_value(char *msg, int value)
{
	if (msg)
		printf("%s\n", msg);
	return (value);
}

void	cleanup_data(t_data *data)
{
	size_t	i;

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
		i = 0;
		while (i < data->head_count)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free (data->forks);
		data->forks = NULL;
	}
}
