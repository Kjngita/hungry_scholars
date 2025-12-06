/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_messenger.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:10:27 by gita              #+#    #+#             */
/*   Updated: 2025/12/06 16:11:31 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

void	announcement_to_screen(t_data *data, t_philo *philo, char *activity)
{
	uint64_t	timestamp_in_milsec;

	pthread_mutex_lock(&data->termination_access);
	if (data->terminate_prog == 1)
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

void	death_notice(t_philo *philo)
{
	uint64_t	timestamp_in_milsec;

	pthread_mutex_lock(&philo->data->printer_access);
	timestamp_in_milsec = simplified_time() - philo->data->start_time_of_prog;
	printf("%lu %zu %s\n", timestamp_in_milsec, philo->id, "died");
	pthread_mutex_unlock(&philo->data->printer_access);
}

void	lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	announcement_to_screen(philo->data, philo, "has taken a fork");
	usleep(philo->data->hunger_endurance * 1000);
	pthread_mutex_unlock(philo->left_fork);
}
