/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:59:52 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/05 17:02:35 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*dup;
	size_t	total;

	total = n * size;
	dup = malloc(total);
	if (!dup)
		return (NULL);
	memset(dup, 0, total);
	return (dup);
}

int	ft_isdigit(int nb)
{
	if (nb >= 48 && nb <= 57)
		return (1);
	else
		return (0);
}

void	syntax(int flag)
{
	if (!flag)
		write(2,"Syntax error: ./philo number_of_
				philosophers time_to_die time_to_eat time_to_sleep
						[number_of_times_each_philosopher_must_eat].\n", 128);
	if (flag == 1)
		write(2, "Syntax error: All the number has to be positive.\n", 49);
	if (flag == 2)
		write(2, "Syntax error: Only digits are allowed.\n", 39);
	if (flag == 3)
		write(2, "Syntax error: Number of philosophers is not valid.\n", 37);
	if (flag == 4)
		write(2, "Syntax error: Arguments has to be bigger than 0.\n", 49);
	if (flag == 5)
		write(2, "Error: malloc.\n", 15);
	if (flag == 6)
		write(2, "Syntax error: Argument too big.\n", 32);
}

int	check_args(int ac, char **av)
{
	char	**str;
	char	*sub;

	str = av;
	if (ac != 5 && ac != 6)
		return (syntax(0), 1);
	str++;
	while (*str)
	{
		if (*str[0] == '-')
			return (syntax(1), 1);
		sub = *str;
		while (*sub)
		{
			if (*sub == '+')
				sub++;
			if (!ft_isdigit(*sub))
				return (syntax(2), 1);
			sub++;
		}
		if (ft_strlen(*str) > 10)
			return (syntax(6), 1);
		str++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sinal;
	int		num;
	char	*str;

	str = (char *)nptr;
	i = 0;
	num = 0;
	sinal = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sinal = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sinal);
}
