/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:59:52 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/16 13:50:59 by aleperei         ###   ########.fr       */
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

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '+')
		str++;
	while (str[i] != '\0')
		i++;
	return (i);
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
