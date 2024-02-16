/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iniciate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:15:50 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/16 16:03:36 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(void)
{
	int	i;

	i = 0;
	while (i < data()->n_philo)
	{
		pthread_mutex_init(&data()->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data()->wrt, NULL);
	pthread_mutex_init(&data()->end, NULL);
	pthread_mutex_init(&data()->meal_eat, NULL);
	return (0);
}

static int	case_one(t_philo *node)
{
	node[0].id = 1;
	node[0].r_fork = &data()->forks[0];
	node[0].last_meal_time = get_time();
	if (pthread_create(&data()->tid[0], NULL, &routine, &data()->philos[0]))
		return (free(data()->forks), free(data()->philos), free(data()->tid),
			syntax(5), 1);
	return (0);
}

int	init_philosophers(t_philo *node)
{
	int	i;

	i = -1;
	data()->start_time = get_time();
	if (data()->n_philo == 1)
	{
		if (case_one(node))
			return (1);
		return (0);
	}
	while (++i < (data()->n_philo))
	{
		node[i].id = i + 1;
		
		if ((node[i].id % 2))
		{
			if (node[i].id == data()->n_philo)
			{
				node[i].r_fork = &data()->forks[0];
				node[i].l_fork = &data()->forks[i];
			}
			else
			{
				node[i].r_fork = &data()->forks[i + 1];
				node[i].l_fork = &data()->forks[i];	
			}
		}
		else
		{
			if (node[i].id == data()->n_philo)
			{
				node[i].r_fork = &data()->forks[0];
				node[i].l_fork = &data()->forks[i];
			}
			else
			{
				node[i].r_fork = &data()->forks[i];
				node[i].l_fork = &data()->forks[i + 1];	
			}

		}
		
		// if (node[i].id == data()->n_philo)
		// 	node[i].l_fork = &data()->forks[0];
		// else
		// 	node[i].l_fork = &data()->forks[i + 1];


		
		node[i].last_meal_time = get_time();
		if (pthread_create(&data()->tid[i], NULL, &routine, &data()->philos[i]))
			return (quit(), syntax(7), 1);
	}
	return (0);
}

// allocate memory for the forks, philos and tid
static int	box_memory(void)
{
	(data()->forks) = ft_calloc(data()->n_philo, sizeof(pthread_mutex_t));
	if (!data()->forks)
		return (syntax(5), 1);
	(data()->philos) = ft_calloc(data()->n_philo, sizeof(t_philo));
	if (!data()->forks)
		return (free(data()->forks), syntax(5), 1);
	(data()->tid) = ft_calloc(data()->n_philo, sizeof(pthread_t));
	if (!data()->tid)
		return (free(data()->forks), free(data()->philos), syntax(5), 1);
	return (0);
}

int	init_struct(char **argv, int argc)
{
	data()->dead = 1;
	data()->n_philo = ft_atoi(argv[1]);
	if (data()->n_philo > 200)
		return (syntax(3), 1);
	data()->time_to_die = (size_t)ft_atoi(argv[2]);
	data()->time_to_eat = (size_t)ft_atoi(argv[3]);
	data()->time_to_sleep = (size_t)ft_atoi(argv[4]);
	if (argc == 6)
		data()->food_need = ft_atoi(argv[5]);
	else
		data()->food_need = -1;
	if (!data()->n_philo || !data()->time_to_die || !data()->time_to_eat
		|| !data()->time_to_sleep || !data()->food_need)
		return (syntax(4), 1);
	if (box_memory() || init_mutex())
		return (1);
	return (0);
}
