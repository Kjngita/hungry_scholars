/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philos_schedule.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:37:20 by gita              #+#    #+#             */
/*   Updated: 2025/12/09 16:11:07 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

/*
Healthy lifestyle designated to philos:
- Wait for all philo threads to be created; redirect to lonely_philo() if needed
- Ask even-number-id philos to delay a bit so the rest can start first and avoid
data racing
- Enter the infinite loop of taking forks -> eat -> sleep -> think. Exit loop
when program needs to stop

Return: NULL when philo threads are not supposed to execute anymore
*/
void	*philo_prog(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (wait_all_threads(philo->data) == 1)
		return (NULL);
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
		claim_forks(philo);
		eat_cleanly(philo);
		sleep_soundly(philo);
		think_boldly(philo);
		if (check_if_stopped(philo->data) > 0)
			break ;
	}
	return (NULL);
}

/*
- To help prevent data races, odd-numbered-id philos will be asked to grab the
left fork first then the right fork. The opposite for even-numbered-id philos.
- Each philo will check themselves right after the moment they acquire the 2nd
fork whether they starved already before continuing further.
(helper function of philo_prog())
*/
void	claim_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork);
		announcement_to_screen(philo->data, philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		announcement_to_screen(philo->data, philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
	}
	if (self_checkup(philo) == -1)
		return ;
	announcement_to_screen(philo->data, philo, "has taken a fork");
}

/*
When philo got both forks and program can still continue, update time of last
meal and usleep for the duration of time_to_eat. Then increment the meals eaten
and unlock fork mutexes for other philos to use.
(helper function of philo_prog())
*/
void	eat_cleanly(t_philo *philo)
{
	if (check_if_stopped(philo->data) > 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
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

/*
When program can still continue, print to screen the sleeping action and usleep
for the time_to_sleep duration.
(helper function of philo_prog())
*/
void	sleep_soundly(t_philo *philo)
{
	if (check_if_stopped(philo->data) > 0)
		return ;
	announcement_to_screen(philo->data, philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

/*
When program can still continue, make calculation to see if philo can afford to
think without dying. If philo can think for at least 2 milisecond, usleep half
of that time (in small 500 microsecond invervals to check if program needs to
stop) before trying to claim forks again.
(helper function of philo_prog())
*/
void	think_boldly(t_philo *philo)
{
	uint64_t	max_thinking;
	uint64_t	start_think;

	if (check_if_stopped(philo->data) > 0)
		return ;
	max_thinking = philo->data->hunger_endurance - philo->data->time_to_sleep
		- philo->data->time_to_eat;
	if (max_thinking > 2)
	{
		announcement_to_screen(philo->data, philo, "is thinking");
		start_think = simplified_time();
		while (simplified_time() - start_think < max_thinking / 2)
		{
			if (check_if_stopped(philo->data) > 0)
				break ;
			usleep(500);
		}
	}
}
