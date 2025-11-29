/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_schedule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:37:20 by gita              #+#    #+#             */
/*   Updated: 2025/11/29 19:04:47 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

void	*philo_prog(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->stop_prog)
			return (NULL);
		if (philo->data->start_time_of_prog)
			break ;
	}
	philo->last_bite = philo->data->start_time_of_prog;
	if (philo->id % 2 == 0)
	{
		announcement_to_screen(philo->data, philo, "is thinking");
		usleep(philo->data->hunger_endurance * 0.2 * 1000);
	}
	while (!philo->data->stop_prog)
	{
		eat_cleanly(philo);
		sleep_soundly(philo);
		think_boldly(philo);
		usleep(100);
	}
	return (NULL);
}

void	eat_cleanly(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	announcement_to_screen(philo->data, philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	announcement_to_screen(philo->data, philo, "has taken a fork");
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
	if (simplified_time() - philo->last_bite > philo->data->hunger_endurance - philo->data->time_to_sleep - philo->data->time_to_eat - 1000)
		usleep(500);
	// think_this_long = philo->data->hunger_endurance	- philo->data->time_to_sleep;
	// announcement_to_screen(philo->data, philo, "is thinking");
	// if (philo->id % 2 == 0)
	// 	usleep(think_this_long * 0.5 * 1000);
	// else
	// 	usleep(think_this_long * 0.8 * 1000);
}
