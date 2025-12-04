/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_schedule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:37:20 by gita              #+#    #+#             */
/*   Updated: 2025/12/04 22:35:07 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

void	*philo_prog(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->head_count == 1)
	{
		lonely_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		announcement_to_screen(philo->data, philo, "is thinking");
		usleep(philo->data->hunger_endurance * 0.2 * 1000);
	}
	while (1)
	{
		if (check_if_stopped(philo->data) == 1)
			break ;
		eat_cleanly(philo);
		sleep_soundly(philo);
		think_boldly(philo);
		// usleep(200);
	}
	return (NULL);
}

void	lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	announcement_to_screen(philo->data, philo, "has taken a fork");
	usleep(philo->data->hunger_endurance * 1000);
	pthread_mutex_unlock(philo->left_fork);
	check_if_starved(philo->data);
}

void	eat_cleanly(t_philo *philo)
{
	claim_forks(philo);
	pthread_mutex_lock(&philo->meal_info_access);
	philo->last_bite = simplified_time();
	pthread_mutex_unlock(&philo->meal_info_access);
	announcement_to_screen(philo->data, philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_info_access);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_info_access);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	claim_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork);
		announcement_to_screen(philo->data, philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		announcement_to_screen(philo->data, philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		announcement_to_screen(philo->data, philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		announcement_to_screen(philo->data, philo, "has taken a fork");
	}
}

void	sleep_soundly(t_philo *philo)
{
	uint64_t	start_nap;

	announcement_to_screen(philo->data, philo, "is sleeping");
	start_nap = simplified_time();
	while (simplified_time() - start_nap < philo->data->time_to_sleep)
	{
		if (check_if_stopped(philo->data) == 1)
			break ;
		usleep(500);
	}
}

void	think_boldly(t_philo *philo)
{
	uint64_t	max_thinking;
	uint64_t	start_think;

	start_think = simplified_time();
	max_thinking = philo->data->hunger_endurance
						- philo->data->time_to_sleep
						- philo->data->time_to_eat;
	announcement_to_screen(philo->data, philo, "is thinking");
	while (simplified_time() - start_think < max_thinking / 2)
	{
		if (check_if_stopped(philo->data) == 1)
			break ;
		usleep(500);
	}
}
