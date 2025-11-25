/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_schedule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:37:20 by gita              #+#    #+#             */
/*   Updated: 2025/11/25 22:24:08 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

void	*philo_prog(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Created thread #%zu\n", philo->id);
	while (1)
	{
		if (philo->data->start_time_of_prog)
		{
			philo->last_bite = philo->data->start_time_of_prog;
			break ;
		}
	}
	if (philo->id % 2 == 0)
	{
		announcement_to_screen(philo->data, philo, "is thinking");
		usleep(1000);	
	}
	while (!philo->data->stop_prog)
	{
		eat_cleanly(philo);
		sleep_soundly(philo);
		think_boldly(philo);
	}
	return (NULL);
}

void	eat_cleanly(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	announcement_to_screen(philo->data, philo, "has taken L fork");
	pthread_mutex_lock(philo->right_fork);
	announcement_to_screen(philo->data, philo, "has taken R fork");
	pthread_mutex_lock(&philo->personal_bodyguard);
	philo->is_eating = 1;
	announcement_to_screen(philo->data, philo, "is eating");
	pthread_mutex_unlock(&philo->personal_bodyguard);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->personal_bodyguard);
	philo->meals_eaten++;
	philo->last_bite = simplified_time();
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->personal_bodyguard);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_soundly(t_philo *philo)
{
	announcement_to_screen(philo->data, philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	think_boldly(t_philo *philo)
{
	announcement_to_screen(philo->data, philo, "is thinking");
	usleep(1000);
}
