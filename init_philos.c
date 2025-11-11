/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:45:48 by gita              #+#    #+#             */
/*   Updated: 2025/11/11 23:02:08 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	register_data(int ac, char **av, t_data *data)
{
	int	i;

	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
	data->philo_threads = malloc(sizeof(pthread_t) * data->nbr_of_philos);
	if (!data->philo_threads)
		return (print_msg_n_return_value("Malloc failed for philo thread", -1));
	data->philo_queue = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philo_queue)
		return (print_msg_n_return_value("Malloc failed for philo queue", -1));
	i = 0;
	while (i < data->nbr_of_philos)
	{
		memset(&data->philo_queue[i], 0, sizeof(t_philo));
		data->philo_queue[i].data = data;
		i++;
	}
	return (0);
}

int	init_threads(t_data *data)
{
	int			i;
	pthread_t	supervisor;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		data->philo_queue[i].id = i + 1;
		if (pthread_create(&data->philo_threads[i], NULL, &start_of_prog,
				&data->philo_queue[i]) != 0)
			return (print_msg_n_return_value("Thread creation failed", -1));
		data->philo_queue[i].thread_no = data->philo_threads[i];
		if (pthread_join(data->philo_threads[i], NULL) != 0)
			return (print_msg_n_return_value("Thread join failed", -1));
		i++;
	}
	if (pthread_create(&supervisor, NULL, &supervise_prog, data) != 0)
		return (print_msg_n_return_value("S-thread creation failed", -1));
	if (pthread_join(supervisor, NULL) != 0)
		return (print_msg_n_return_value("S-thread join failed", -1));
	return (0);
}

void	*supervise_prog(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	printf("\nCreated superviser thread\n");
	printf("Time to die=%i eat=%i sleep=%i\n", data->time_to_die, data->time_to_eat, data->time_to_sleep);
	printf("Number of meals = %i\n", data->number_of_meals);
	return (NULL);
}

void	*start_of_prog(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Created thread #%zu\n", philo->id);
	printf("Ate=%i Enough=%zu Slept=%i\n", philo->alr_ate, philo->ate_enough_times, philo->alr_slept);
	printf("Check time to die = %i\n", philo->data->time_to_die); //invalid read

	return (NULL);
}

