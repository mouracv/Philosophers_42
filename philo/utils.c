/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:59:52 by aleperei          #+#    #+#             */
/*   Updated: 2024/01/25 18:02:47 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		printf(("Syntax error: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"));
	if (flag == 1)
		printf("Syntax error: All the number has to be positive\n");
	if (flag == 2)
		printf("Syntax error: Only digits are allowed\n");
	if (flag == 3)
		printf("");
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
