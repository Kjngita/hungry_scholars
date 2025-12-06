/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_messenger.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:10:27 by gita              #+#    #+#             */
/*   Updated: 2025/12/08 18:49:56 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

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

	pthread_mutex_lock(&data->termination_access);
	if (data->terminate_prog > 0)
	{
		pthread_mutex_unlock(&data->termination_access);
		return ;
	}
	pthread_mutex_unlock(&data->termination_access);
	pthread_mutex_lock(&data->printer_access);
	timestamp_in_milsec = simplified_time() - data->start_time_of_prog;
	printf("%lu %zu %s\n", timestamp_in_milsec, philo->id, activity);
	pthread_mutex_unlock(&data->printer_access);
}

/*
- Lock the mutex for printing
- Get the timestamp of the current printing action and print death info
- Release the mutex for printing
*/
void	death_notice(t_data *data, size_t dead_philo_id)
{
	uint64_t	timestamp_in_milsec;

	pthread_mutex_lock(&data->printer_access);
	timestamp_in_milsec = simplified_time() - data->start_time_of_prog;
	printf("%lu %zu %s\n", timestamp_in_milsec, dead_philo_id, "died");
	pthread_mutex_unlock(&data->printer_access);
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
