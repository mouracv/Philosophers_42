/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:03:47 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/07 17:16:58 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	quit(void)
{
	int	i;

	i = -1;
	while (++i < data()->n_philo)
		pthread_join(data()->tid[i], NULL);
	i = -1;
	while (++i < data()->n_philo)
		pthread_mutex_destroy(&data()->forks[i]);
	pthread_mutex_destroy(&data()->wrt);
	pthread_mutex_destroy(&data()->end);
	pthread_mutex_destroy(&data()->food);
	if (data()->philos)
		free(data()->philos);
	if (data()->forks)
		free(data()->forks);
	if (data()->tid)
		free(data()->tid);
}

static void	go_to_grave(void)
{
	int		i;
	size_t	tm;
	size_t	last_meal;

	i = 0;
	tm = 0;
	last_meal = 0;
	while (i < data()->n_philo)
	{
		pthread_mutex_lock(&data()->food);
		last_meal = data()->philos[i].last_meal_time;
		pthread_mutex_unlock(&data()->food);
		tm = get_time();
		if ((tm - last_meal) >= data()->time_to_die)
		{
			print_status("died", &data()->philos[i]);
			pthread_mutex_lock(&data()->end);
			data()->dead = 0;
			pthread_mutex_unlock(&data()->end);
			break ;
		}
		i++;
	}
	return ;
}

static void	full_philo(void)
{
	int	i;

	i = 0;
	if (data()->food_need < 0)
		return ;
	while (i < data()->n_philo
		&& data()->philos[i].food_eaten >= data()->food_need)
	{
		i++;
	}
	if (i == data()->n_philo)
	{
		pthread_mutex_lock(&data()->end);
		data()->dead = 0;
		pthread_mutex_unlock(&data()->end);
	}
	return ;
}

void	cell_guard(void)
{
	while (end(&data()->end, &data()->dead))
	{
		full_philo();
		if (!end(&data()->end, &data()->dead))
			break ;
		go_to_grave();
	}
}
