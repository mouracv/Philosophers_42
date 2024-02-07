/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:33:25 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/07 16:27:04 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '+')
		str++;
	while (str[i] != '\0')
		i++;
	return (i);
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
		usleep(time / 10);
}

int	case_one(t_philo *node)
{
	node[0].id = 1;
	node[0].r_fork = &data()->forks[0];
	node[0].last_meal_time = get_time();
	if (pthread_create(&data()->tid[0], NULL, &routine, &data()->philos[0]))
		return (free(data()->forks), free(data()->philos), free(data()->tid),
			syntax(5), 1);
	return (0);
}

int    end(pthread_mutex_t *end, int   *status)
{
    int tmp = 0;
    pthread_mutex_lock(end);
    tmp = *status;
    pthread_mutex_unlock(end);
    return (tmp);
}
