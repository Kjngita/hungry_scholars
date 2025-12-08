/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:07 by gita              #+#    #+#             */
/*   Updated: 2025/12/08 22:32:02 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

/*	START OF PROGRAM
- Validate input
- Memset the t_data struct with 0, then fill in data from input and time 
- Initialize the threads (philos and supervisor)
- Call pthread_join to wait for philo and supervisor threads to finish tasks
- Destroy mutexes and clean up when threads are done executing
- Return (end the program) with 0 on success or 1 on errors
*/
int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	supervisor;

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
	if (wait_threads_to_finish(&data, &supervisor) == -1)
	{
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}

/*
Wait for philo and supervisor threads to finish executing,
then destroy mutex for meal info in each philo thread.

Return: 0 on success, -1 on errors
*/
int	wait_threads_to_finish(t_data *data, pthread_t *supervisor)
{
	if (pthread_join(*supervisor, NULL) != 0)
		return (print_err_n_return_value("S-thread join failed", -1));
	if (join_threads(data, data->head_count) == -1)
		return (-1);
	if (dump_meal_mutex(data, data->head_count) == -1)
		return (-1);
	return (0);
}

/*
Special case for only 1 philo.
*/
void	lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	announcement_to_screen(philo->data, philo, "has taken a fork");
	usleep(philo->data->hunger_endurance * 1000);
	pthread_mutex_unlock(philo->left_fork);
}
