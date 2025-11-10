/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:07 by gita              #+#    #+#             */
/*   Updated: 2025/11/10 19:03:45 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"


int	main(int ac, char **av)
{
	int	i;
	int number_of_philos;

	if (!(ac == 5 || ac == 6))
		return (print_msg_n_return_value("Incorrect number of arguments", 1));
	i = 1;
	while (i < ac)
	{
		if (validate_args(av[i]) == -1)
			return (1);
		i++;
	}
	number_of_philos = ft_atoi(av[1]);
	// if (init_philo(number_of_philos, ac, av) == -1)
	// 	return (1);
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

int	validate_args(char *arg)
{
	int	number;

	if (!arg)
		return (-1);
	number = ft_atoi(arg);
	if (number <= 0)
		return (print_msg_n_return_value("Invalid argument", -1));
	return (0);
}

int	print_msg_n_return_value(char *msg, int value)
{
	if (msg)
		printf("%s\n", msg);
	return (value);
}
