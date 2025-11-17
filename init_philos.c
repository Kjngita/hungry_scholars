/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:45:48 by gita              #+#    #+#             */
/*   Updated: 2025/11/17 22:53:03 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	register_data(int ac, char **av, t_data *data)
{
	int	i;

	basic_data(ac, av, data);
	data->philo_threads = malloc(sizeof(pthread_t) * data->nbr_of_philos);
	if (!data->philo_threads)
		return (print_msg_n_return_value("Malloc failed for philo thread", -1));
	data->philo_queue = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philo_queue)
		return (print_msg_n_return_value("Malloc failed for philo queue", -1));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos);
	if (!data->forks)
		return (print_msg_n_return_value("Malloc failed for forks", -1));
	i = 0;
	while (i < data->nbr_of_philos)
	{
		memset(&data->philo_queue[i], 0, sizeof(t_philo));
		data->philo_queue[i].data = data;
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (print_msg_n_return_value("Fork pthread init failed", -1));
		i++;
	}
	return (0);
}

void	basic_data(int ac, char **av, t_data *data)
{
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
}

int	init_threads(t_data *data)
{
	int			i;
	pthread_t	supervisor;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		data->philo_queue[i].id = i + 1;
		if (pthread_create(&data->philo_threads[i], NULL, &philo_prog,
				&data->philo_queue[i]) != 0) // || i == 3)
			return (join_threads(data, i));
		data->philo_queue[i].thread_no = data->philo_threads[i];
		i++;
	}
	if (join_threads(data, data->nbr_of_philos) == -1)
		return (-1);
	data->start_time_of_prog = simplified_time();
	if (pthread_create(&supervisor, NULL, &supervise_prog, data) != 0)
		return (print_msg_n_return_value("S-thread creation failed", -1));
	if (pthread_join(supervisor, NULL) != 0)
		return (print_msg_n_return_value("S-thread join failed", -1));
	return (0);
}

int	join_threads(t_data *data, int quantity)
{
	int	i;

	i = 0;
	while (i < quantity)
	{
		if (pthread_join(data->philo_threads[i], NULL) != 0)
			return (print_msg_n_return_value("Thread join failed", -1));
		i++;
	}
	if (i < data->nbr_of_philos)
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
	// while (!philo->starved_to_death)
	// {
	// 	printf("%zu is thinking\n", philo->id);
	// }
	return (NULL);
}

void	*supervise_prog(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	printf("\nCreated superviser thread\n");
	// printf("Time to die=%i eat=%i sleep=%i\n", data->time_to_die, data->time_to_eat, data->time_to_sleep);
	// printf("Number of meals = %i\n", data->number_of_meals);
	printf("Check prog start time %ld\n", data->start_time_of_prog);
	return (NULL);
}

time_t	simplified_time()
{
	struct timeval	this_moment;

	if (gettimeofday(&this_moment, NULL))
		return(print_msg_n_return_value("Error getting time", -1));
	return (((this_moment.tv_sec * 1000) + (this_moment.tv_usec / 1000)));
}
