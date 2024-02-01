/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iniciate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:15:50 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/01 16:05:48 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Funcao que  contem a miha struct
t_box  *data(void)
{
    static t_box geral;
    
    return (&geral);
}

//Return the time in milliseconds
size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//Imitation of usleep
void	ft_usleep(size_t time)
{
	size_t	start;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
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

// colocar o i como argumento para usar ele como index
int	init_philosophers(t_philo *node)
{
	int	i;

	i = -1;
	data()->start_time = get_time();
	if (data()->n_philo == 1)
	{
		node[0].id = 0;
		node[0].r_fork = &data()->forks[0];
		node[0].last_meal_time = get_time();
		if (pthread_create(&data()->tid[0], NULL, &routine, &data()->philos[0]))
			return (free(data()->forks), free(data()->philos),
				free(data()->tid), syntax(5), 1);
		return (0);
	}
	while (++i < (data()->n_philo))
	{
		node[i].dead = 1;
		node[i].id = i + 1;
		node[i].r_fork = &data()->forks[i];
		if (node[i].id == data()->n_philo)
			node[i].l_fork = &data()->forks[0];
		else
			node[i].l_fork = &data()->forks[i + 1];
		node[i].last_meal_time = get_time();
		if (pthread_create(&data()->tid[i], NULL, &routine, &data()->philos[i]))
			return (free(data()->forks), free(data()->philos),
				free(data()->tid), syntax(5), 1);
	}
	return (0);
}

//allocate memory for the forks, philos and tid
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
	if (data()->n_philo > 200)
		return (syntax(3), 1);
	data()->time_to_die = (size_t)ft_atoi(argv[2]);
	data()->time_to_eat = (size_t)ft_atoi(argv[3]);
	data()->time_to_sleep = (size_t)ft_atoi(argv[4]);
	data()->dead = 1;
	if (argv == 6)
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
