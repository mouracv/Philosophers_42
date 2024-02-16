/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:54:04 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/16 15:52:37 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping_philo(t_philo *node)
{
	if (!end(&data()->end, &data()->dead))
		return (1);
	print_status("is sleeping", node);
	ft_usleep(data()->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *node)
{
	if (!end(&data()->end, &data()->dead))
		return (1);
	print_status("is thinking", node);
	return (0);
}

static void	drop_forks(t_philo *node)
{
		pthread_mutex_unlock(node->l_fork);
		pthread_mutex_unlock(node->r_fork);
}

static void	get_forks(t_philo *node)
{

		pthread_mutex_lock(node->r_fork);
		print_status("has taken a fork", node);
		pthread_mutex_lock(node->l_fork);
		print_status("has taken a fork", node);
}

int	eating(t_philo *node)
{
	if (!end(&data()->end, &data()->dead))
		return (1);
	get_forks(node);
	print_status("is eating", node);
	ft_usleep(data()->time_to_eat);
	pthread_mutex_lock(&data()->meal_eat);
	node->last_meal_time = get_time();
	node->food_eaten++;
	pthread_mutex_unlock(&data()->meal_eat);
	drop_forks(node);
	return (0);
}



/*static void	get_forks(t_philo *node)
{
	if (node->id == data()->n_philo)
	{
		pthread_mutex_lock(node->l_fork);
		print_status("has taken a fork", node);
		pthread_mutex_lock(node->r_fork);
		print_status("has taken a fork", node);
	}
	else
	{
		pthread_mutex_lock(node->r_fork);
		print_status("has taken a fork", node);
		pthread_mutex_lock(node->l_fork);
		print_status("has taken a fork", node);
	}
}*/


/*static void	drop_forks(t_philo *node)
{
	if (node->id == data()->n_philo)
	{
		pthread_mutex_unlock(node->r_fork);
		pthread_mutex_unlock(node->l_fork);
	}
	else
	{
		pthread_mutex_unlock(node->l_fork);
		pthread_mutex_unlock(node->r_fork);
	}
}*/