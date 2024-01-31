/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iniciate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:15:50 by aleperei          #+#    #+#             */
/*   Updated: 2024/01/31 16:28:05 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	init_mutex(void)
{
	int	i;

	i = 0;
	while (i < data()->n_philo)
	{
		pthread_mutex_init(&data()->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data()->wrt, NULL);
	return (0);
}

int	init_philosophers(t_philo *node)
{
	int	i;

	i = -1;
	data()->start_time = get_time();
	if (data()->n_philo == 1)
	{
		node[i].r_fork = &data()->forks[0];
		node[i].time_to_die = data()->time_to_die;
		if (pthread_create(&data()->tid[i], NULL, &routine, &data()->philos[i]))
			return (free(data()->forks), free(data()->philos),
				free(data()->tid), syntax(5), 1);
		return (0);
	}
	node[data()->n_philo - 1].time_to_die = data()->time_to_die;
	node[data()->n_philo - 1].id = data()->n_philo;
	node[data()->n_philo - 1].l_fork = &data()->forks[0];
	node[data()->n_philo - 1].r_fork = &data()->forks[data()->n_philo - 1];
	while (++i < (data()->n_philo - 1))
	{
        //criar primeiro os numero impares 
		node[i].id = i + 1;
		node[i].r_fork = &data()->forks[i];
		node[i].l_fork = &data()->forks[i + 1];
		node[i].time_to_die = data()->time_to_die;
		if (pthread_create(&data()->tid[i], NULL, &routine, &data()->philos[i]))
			return (free(data()->forks), free(data()->philos),
				free(data()->tid), syntax(5), 1);
	}
	return (0);
}

int	box_memory(void)
{
	data()->forks = ft_calloc(data()->n_philo, sizeof(pthread_mutex_t));
	if (!data()->forks)
		return (syntax(5), 1);
	data()->philos = ft_calloc(data()->n_philo, sizeof(t_philo));
	if (!data()->forks)
		return (free(data()->forks), syntax(5), 1);
	data()->tid = ft_calloc(data()->n_philo, sizeof(pthread_t));
	if (!data()->tid)
		return (free(data()->forks), free(data()->philos), syntax(5), 1);
	return (0);
}

int	init_struct(char **argv, int argc)
{
	data()->n_philo = ft_atoi(argv[1]);
	if (data()->n_philo < 0 || data()->n_philo > 200)
		return (syntax(3), 1);
	data()->time_to_die = (size_t)ft_atoi(argv[2]);
	data()->time_to_eat = (size_t)ft_atoi(argv[3]);
	data()->time_to_sleep = (size_t)ft_atoi(argv[4]);

	if (data()->n_philo <= 0 || !data()->time_to_die || !data()->time_to_eat
		|| !data()->time_to_sleep)
		return (syntax(4), 1);
	if (argv == 6)
		data()->food_need = ft_atoi(argv[5]);
	else
		data()->food_need = -1;

	if (box_memory() || init_mutex())
		return (1);
	return (0);
}
