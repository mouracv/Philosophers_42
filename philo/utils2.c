/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:33:25 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/21 12:58:34 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	syntax(int flag)
{
	if (!flag)
	{
		write(2, "Syntax error: ./philo number_of_philosophers ", 45);
		write(2, "time_to_die time_to_eat time_to_sleep ", 38);
		write(2, "[number_of_times_each_philosopher_must_eat].\n", 45);
	}
	if (flag == 1)
		write(2, "Syntax error: All the number has to be positive.\n", 49);
	if (flag == 2)
		write(2, "Syntax error: Only digits are allowed.\n", 39);
	if (flag == 3)
		write(2, "Syntax error: Number of philosophers is not valid.\n", 51);
	if (flag == 4)
		write(2, "Syntax error: Arguments has to be bigger than 0.\n", 49);
	if (flag == 5)
		write(2, "Error: malloc.\n", 15);
	if (flag == 6)
		write(2, "Syntax error: Argument too big.\n", 32);
	if (flag == 7)
		write(2, "Error: Failed to create pthread.\n", 33);
}

// Return the time in milliseconds
size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// Imitation of usleep
void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time && end(&data()->end, &data()->dead))
		usleep(100);
}

int	end(pthread_mutex_t *end, int *status)
{
	int	tmp;

	tmp = 0;
	pthread_mutex_lock(end);
	tmp = *status;
	pthread_mutex_unlock(end);
	return (tmp);
}

void	set_mtx_value(pthread_mutex_t *mtx, int *var, int new_value)
{
	pthread_mutex_lock(mtx);
	*var = new_value;
	pthread_mutex_unlock(mtx);
}
