/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:03:47 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/05 17:00:47 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_mutex(void)
{
	int	i;

	i = -1;
	while (++i < data()->n_philo)
		pthread_mutex_destroy(&data()->forks[i]);
	pthread_mutex_destroy(&data()->wrt);
}

void	quit(void)
{
	int	i;

	i = -1;
	while (++i < data()->n_philo)
		pthread_join(data()->tid[i], NULL);
	clear_mutex();
	if (data()->philos)
		free(data()->philos);
	if (data()->forks)
		free(data()->forks);
	if (data()->tid)
		free(data()->tid);
}

static void	go_to_grave(t_philo *node)
{
	int	i;

	i = 0;
	while (i < data()->n_philo)
	{
		if ((get_time() - node[i].last_meal_time) >= data()->time_to_die)
		{
			print_status("died", &node[i]);
			data()->dead = 0;
			break ;
		}
		i++;
	}
	return ;
}

static void	full_philo(t_philo *node)
{
	int	i;
	int	times;

	i = 0;
	times = 0;
	if (data()->food_need < 0)
		return ;
	while (data()->food_need && i < data()->n_philo
		&& node[i].food_eaten >= data()->food_need)
	{
		times++;
		i++;
	}
	if (times == data()->n_philo)
	{
		data()->dead = 0;
		return ;
	}
	return ;
}

void	cell_guard(void)
{
	while (data()->dead)
	{
		full_philo(data()->philos);
		if (!data()->dead)
			break ;
		go_to_grave(data()->philos);
	}
}
