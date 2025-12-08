/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:10:27 by gita              #+#    #+#             */
/*   Updated: 2025/12/08 23:02:38 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

/*
Called by each philo thread. Threads will be on standby until either program
needs to stop due to error in init_threads or terminate_prog value is changed
to 0 by main to signal threads to start execution.
(helper function of philo_prog())

Return: 0 when can start, 1 when need to stop
*/
int	wait_all_threads(t_data *data)
{
	while (1)
	{
		if (check_if_stopped(data) == 0)
			return (0);
		if (check_if_stopped(data) == 1)
			return (1);
	}
}

/*
Function to print out actions of philos
- First, lock the mutex for termination checking. Release that mutex, if program
needs to stop then return, otherwise continue
- Lock the mutex for printing
- Get the timestamp of the current printing action and print needed info
- Release the mutex for printing
*/
void	announcement_to_screen(t_data *data, t_philo *philo, char *activity)
{
	uint64_t	timestamp_in_milsec;

	pthread_mutex_lock(&data->printer_access);
	if (check_if_stopped(data) > 0)
	{
		pthread_mutex_unlock(&data->printer_access);
		return ;
	}
	timestamp_in_milsec = simplified_time() - data->start_time_of_prog;
	printf("%lu %zu %s\n", timestamp_in_milsec, philo->id, activity);
	pthread_mutex_unlock(&data->printer_access);
}

/*
- Retrieve the time of last meal that is protected by meal info mutex
- If philo starved, set the value of terminate_prog to 2 for supervisor thread
to know to drop checking all philos in loop and go straight to printing death
(helper function of claim_forks())

Return: 0 on full health, -1 on starvation
*/
int	self_checkup(t_philo *philo)
{
	uint64_t	last_bite;

	pthread_mutex_lock(&philo->meal_info_access);
	last_bite = philo->last_bite;
	pthread_mutex_unlock(&philo->meal_info_access);
	if (philo->data->hunger_endurance < simplified_time() - last_bite)
	{
		pthread_mutex_lock(&philo->data->termination_access);
		philo->data->terminate_prog = 2;
		philo->data->dead_philo_id = philo->id;
		pthread_mutex_unlock(&philo->data->termination_access);
		return (-1);
	}
	return (0);
}
