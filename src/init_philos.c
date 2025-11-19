/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:45:48 by gita              #+#    #+#             */
/*   Updated: 2025/11/19 22:56:15 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	register_data(int ac, char **av, t_data *data)
{
	size_t	i;

	basic_data(ac, av, data);
	data->philo_threads = malloc(sizeof(pthread_t) * data->head_count);
	if (!data->philo_threads)
		return (print_msg_n_return_value("Malloc failed for philo thread", -1));
	data->philo_queue = malloc(sizeof(t_philo) * data->head_count);
	if (!data->philo_queue)
		return (print_msg_n_return_value("Malloc failed for philo queue", -1));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->head_count);
	if (!data->forks)
		return (print_msg_n_return_value("Malloc failed for forks", -1));
	i = 0;
	while (i < data->head_count)
	{
		memset(&data->philo_queue[i], 0, sizeof(t_philo));
		data->philo_queue[i].data = data;
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (print_msg_n_return_value("Fork pthread init failed", -1));
		assign_forks(data, i);
		i++;
	}
	return (0);
}

void	basic_data(int ac, char **av, t_data *data)
{
	data->head_count = ft_atoi(av[1]);
	data->hunger_endurance = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
}

void	assign_forks(t_data *data, size_t i)
{
	data->philo_queue[i].left_fork = &data->forks[i];
	if (data->head_count > 1)
	{
		if (i + 1 == data->head_count)
			data->philo_queue[i].right_fork = &data->forks[0];
		else
			data->philo_queue[i].right_fork = &data->forks[i + 1];
	}
}

int	init_threads(t_data *data)
{
	size_t		i;
	pthread_t	supervisor;

	i = 0;
	while (i < data->head_count)
	{
		data->philo_queue[i].id = i + 1;
		if (pthread_create(&data->philo_threads[i], NULL, &philo_prog,
				&data->philo_queue[i]) != 0) // || i == 3)
			return (join_threads(data, i));
		// data->philo_queue[i].thread_no = data->philo_threads[i];
		i++;
	}
	data->start_time_of_prog = simplified_time();
	if (pthread_create(&supervisor, NULL, &supervise_prog, data) != 0)
		return (print_msg_n_return_value("S-thread creation failed", -1));
	if (join_threads(data, data->head_count) == -1)
		return (-1);
	if (pthread_join(supervisor, NULL) != 0)
		return (print_msg_n_return_value("S-thread join failed", -1));
	return (0);
}

int	join_threads(t_data *data, size_t quantity)
{
	size_t	i;

	i = 0;
	while (i < quantity)
	{
		if (pthread_join(data->philo_threads[i], NULL) != 0)
			return (print_msg_n_return_value("Thread join failed", -1));
		i++;
	}
	if (i < data->head_count)
		return (print_msg_n_return_value("Thread creation failed midway", -1));
	return (0);
}

void	*philo_prog(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Created thread #%zu\n", philo->id);
	// printf("Ate=%i Enough=%zu Slept=%i\n", philo->alr_ate, philo->ate_enough_times, philo->alr_slept);
	// printf("Check time to die = %i\n", philo->data->time_to_die);
	while (1)
		if (philo->data->start_time_of_prog)
			break ;
	while (!philo->data->stop_prog)
	{
		//eat, sleep, think, repeat;
	}
	return (NULL);
}

uint64_t	simplified_time()
{
	struct timeval	this_moment;

	if (gettimeofday(&this_moment, NULL))
		return(print_msg_n_return_value("Error getting time", -1));
	return (((this_moment.tv_sec * 1000) + (this_moment.tv_usec / 1000)));
}
