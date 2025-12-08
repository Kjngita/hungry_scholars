/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_supervisor_tasks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:02:33 by gita              #+#    #+#             */
/*   Updated: 2025/12/08 23:03:38 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

/*
Repetitive tasks for supervisor thread:
- Check if program needs to stop
- Check if any philo thread died
- In case there is minimum meals enforced, check if all philos ate enough
- Small usleep break to prevent burnout

Return: NULL when program needs to stop
*/
void	*supervise_prog(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_if_stopped(data) == 1)
			break ;
		if (check_if_starved(data) == 1)
			break ;
		if (data->forced_meals > 0 && check_if_all_full(data) == 1)
			break ;
		usleep(100);
	}
	return (NULL);
}

/*
Check if program needs to stop using mutex for updating value of terminate_prog

Return: 0 on program can continue, 1 on program needs to stop, 2 on when some
philo thread died and needs to notify supervisor thread to print death asap
*/
int	check_if_stopped(t_data *data)
{
	int	gotta_stop;

	pthread_mutex_lock(&data->termination_access);
	gotta_stop = data->terminate_prog;
	pthread_mutex_unlock(&data->termination_access);
	return (gotta_stop);
}

/*
Go through all philos, check if they are not famished. Everytime moving on to a
new philo, check if some philo submitted request to print their death.
(helper function of supervise_prog())

Return: 0 on everyone surviving, 1 on philo death
*/
int	check_if_starved(t_data *data)
{
	size_t		i;
	uint64_t	last_bite;

	i = 0;
	while (i < data->head_count)
	{
		if (check_if_stopped(data) == 2)
		{
			death_notice(data, data->dead_philo_id);
			return (1);
		}
		pthread_mutex_lock(&data->philo_queue[i].meal_info_access);
		last_bite = data->philo_queue[i].last_bite;
		pthread_mutex_unlock(&data->philo_queue[i].meal_info_access);
		if (data->hunger_endurance < simplified_time() - last_bite)
		{
			pthread_mutex_lock(&data->termination_access);
			data->terminate_prog = 1;
			pthread_mutex_unlock(&data->termination_access);
			death_notice(data, data->philo_queue[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
- Go through all philos and check if they've eaten enough required meals. Every
time moving on to a new philo, check if some philo reported their death.
- Increase the counter when a philo ate enough. After checking everyone, compare
counter to number of philo to detemine if program needs to keep running.
(helper function of supervise_prog())

Return: 0 on program needs to continue, 1 on program can stop
*/
int	check_if_all_full(t_data *data)
{
	int		i;
	size_t	happy_philos;

	i = -1;
	happy_philos = 0;
	while (++i < (int)data->head_count)
	{
		if (check_if_stopped(data) == 2)
		{
			death_notice(data, data->dead_philo_id);
			return (1);
		}
		pthread_mutex_lock(&data->philo_queue[i].meal_info_access);
		if (data->philo_queue[i].meals_eaten >= data->forced_meals)
			happy_philos++;
		pthread_mutex_unlock(&data->philo_queue[i].meal_info_access);
	}
	if (happy_philos == data->head_count)
	{
		pthread_mutex_lock(&data->termination_access);
		data->terminate_prog = 1;
		pthread_mutex_unlock(&data->termination_access);
		return (1);
	}
	return (0);
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
