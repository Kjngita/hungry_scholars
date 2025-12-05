/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:07 by gita              #+#    #+#             */
/*   Updated: 2025/12/05 17:59:29 by gita             ###   ########.fr       */
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
		dump_meal_mutex(&data, data.head_count);
		cleanup_data(&data);
		return (1);
	}
	if (merge_threads_back(&data, &supervisor) == -1)
		return (1);
	cleanup_data(&data);
	return (0);
}

int	merge_threads_back(t_data *data, pthread_t *supervisor)
{
	if (pthread_join(*supervisor, NULL) != 0)
		return (print_err_n_return_value("S-thread join failed", -1));
	if (join_threads(data, data->head_count) == -1)
		return (-1);
	if (dump_meal_mutex(data, data->head_count) == -1)
		return (-1);
	return (0);
}
