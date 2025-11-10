/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:45:48 by gita              #+#    #+#             */
/*   Updated: 2025/11/10 19:06:41 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	init_philo(int number_of_philos, int ac, char **av)
{
	int				i;
	t_mastermind	supervisor;
	pthread_t		threads[number_of_philos];
	
	memset(&supervisor, 0, sizeof(t_mastermind));
	i = 0;
	while (i < number_of_philos)
	{
		// supervisor.philo_queue[i] = create_philo(ac, av);
		if (pthread_create(&threads[i], NULL,
				&start_of_prog, NULL) == -1)
			return (print_msg_n_return_value("Thread creation failed", -1));
		// pthread_join(threads[i], NULL);
		i++;
	}

	return (0);
}

// t_philo	create_philo(int ac, char **av)
// {
// 	t_philo	one_guy;

// 	one_guy.time_to_die = ft_atoi(av[2]);
// 	one_guy.time_to_eat = ft_atoi(av[3]);
// 	one_guy.time_to_sleep = ft_atoi(av[4]);
// 	if (ac == 6)
// 		one_guy.number_of_meals = ft_atoi(av[5]);
// 	return (one_guy);
// }

void	*start_of_prog(void *arg)
{
	(void)arg;
	printf("Created a thread\n");
	return (NULL);
}
