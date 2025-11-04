/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:45:07 by gita              #+#    #+#             */
/*   Updated: 2025/11/04 22:20:48 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philos.h"

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
		nbr = (nbr * 10) + str[i] % 10;
		i++;
	}
	nbr = nbr * sign;
	return (nbr);
}

int	main (int ac, char **av)
{
	int	i;

	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (i < ac)
		{
			if (validate_args(av[i]) == -1)
				return (1);
			i++;
		}
		int number_of_philosophers = ft_atoi(av[1]);
		int time_to_die = ft_atoi(av[2]);
		int time_to_eat = ft_atoi(av[3]);
		int time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
		{
			int number_of_meals = ft_atoi(av[5]);
		}
	}
}

int	validate_args(char *arg)
{
	int	number;

	if (!arg)
		return (-1);
	number = ft_atoi(arg);
	if (number <= 0)
		return (-1);
	return (0);
}
