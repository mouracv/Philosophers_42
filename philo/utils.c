/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:59:52 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/21 13:00:55 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int nb)
{
	if (nb >= 48 && nb <= 57)
		return (1);
	else
		return (0);
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
		str++;
	}
	return (0);
}

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

static long	check_limits(long num)
{
	if (num > INT_MAX || num < INT_MIN)
		return (-1);
	return (num);
}

long	ft_atoi(const char *str)
{
	int		sn;
	long	num;

	sn = 1;
	num = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		sn = (*str == '+') - (*str == '-');
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		num = num * 10 + *str - '0';
		str++;
	}
	num = check_limits(num * sn);
	return (num);
}
