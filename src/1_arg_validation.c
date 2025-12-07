/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_arg_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:56:48 by gita              #+#    #+#             */
/*   Updated: 2025/12/04 23:05:51 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_philo.h"

/*
Perform check on user input whether or not:
- Argument count is of acceptable quantity
- Arguments are positive integers smaller or equal to INT_MAX

Return: 0 on no error, -1 on errors
*/
int	validate_args(int ac, char **av)
{
	int	i;
	int	number;

	if (!(ac == 5 || ac == 6))
		return (print_err_n_return_value("Incorrect number of args", -1));
	if (!av || !*av)
		return (print_err_n_return_value("Could not read av", -1));
	i = 1;
	while (i < ac)
	{
		number = philo_atoi(av[i]);
		if (number <= 0)
			return (print_err_n_return_value("Invalid argument", -1));
		i++;
	}
	return (0);
}

/*
Turn a string to integer. Skip spaces at the beginning and the end.
Other than 1 possible sign for the number, accept only digits.

Return: -1 on errors (not standard/too big integer) or the converted integer
*/
int	philo_atoi(char *str)
{
	size_t	i;
	long	nbr;
	int		sign;

	if (!str)
		return (-1);
	i = 0;
	nbr = 0;
	sign = 1;
	philo_atoi_beginning(str, &i, &sign);
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

/*
Skip spaces in user input, then accept only 1 sign for the number if any
(helper function of philo_atoi())
*/
void	philo_atoi_beginning(char *str, size_t *i, int *sign)
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
