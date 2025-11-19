/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:56:48 by gita              #+#    #+#             */
/*   Updated: 2025/11/17 20:57:15 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

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
	ft_atoi_beginning(str, &i, &sign);
	while (str[i] && str[i] != ' ')
	{
		if (nbr > INT_MAX || str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = (nbr * 10 + str[i]) - '0';
		i++;
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != 0)
		return (-1);
	return (nbr * sign);
}

void	ft_atoi_beginning(char *str, size_t *i, int *sign)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}
