/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:03:47 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/09 15:04:38 by aleperei         ###   ########.fr       */
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
	pthread_mutex_destroy(&data()->meal_eat);
	if (data()->philos)
		free(data()->philos);
	if (data()->forks)
		free(data()->forks);
	if (data()->tid)
		free(data()->tid);
}

void set_mtx_value(pthread_mutex_t *mtx, int *var, int new_value)
{
	pthread_mutex_lock(mtx);
	*var = new_value;
	pthread_mutex_unlock(mtx);
}

static void	go_to_grave(void)
{
	int		i;

	i = 0;
	while (i < data()->n_philo)
	{
		pthread_mutex_lock(&data()->meal_eat);
		if ((get_time() - data()->philos[i].last_meal_time) >= data()->time_to_die)
		{
			print_status("died", &data()->philos[i]);
			set_mtx_value(&data()->end, &data()->dead, 0);
			pthread_mutex_unlock(&data()->meal_eat);
			break ;
		}
		pthread_mutex_unlock(&data()->meal_eat);
		i++;
	}
	return ;
}

static void	full_philo(void)
{
	int	i;
	int	times;

	i = 0;
	times = 0;
	if (data()->food_need < 0)
		return ;
	while (i < data()->n_philo)
	{
		pthread_mutex_lock(&data()->meal_eat);
		if (data()->philos[i].food_eaten >= data()->food_need)
			times++;
		pthread_mutex_unlock(&data()->meal_eat);
		i++;
	}
	if (times == data()->n_philo)
		set_mtx_value(&data()->end, &data()->dead, 0);

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
