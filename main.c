/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:07 by gita              #+#    #+#             */
/*   Updated: 2025/11/11 22:42:50 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!(ac == 5 || ac == 6))
		return (print_msg_n_return_value("Incorrect number of arguments", 1));
	if (validate_args(ac, av) == -1)
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (register_data(ac, av, &data) == -1)
		return (1);
	if (init_threads(&data) == -1)
		return (1);
	printf("Got here\n");
	cleanup_data(&data);
	return (0);
}

int	print_msg_n_return_value(char *msg, int value)
{
	if (msg)
		printf("%s\n", msg);
	return (value);
}

int	validate_args(int ac, char **av)
{
	int	i;
	int	number;

	if (!av || !*av)
		return (-1);
	i = 1;
	while (i < ac)
	{
		number = ft_atoi(av[i]);
		if (number <= 0)
			return (print_msg_n_return_value("Invalid argument", -1));
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	size_t	i;
	long	nbr;
	int		sign;

	if (!str)
		return (-1);
	i = 0;
	nbr = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (nbr > INT_MAX || str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = (nbr * 10 + str[i]) - '0';
		i++;
	}
	return (nbr * sign);
}

void	cleanup_data(t_data *data)
{
	if (data->philo_threads)
		free (data->philo_threads);
	if (data->philo_queue)
		free (data->philo_queue);
}