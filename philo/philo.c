/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/07 17:18:31 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *str, t_philo *node)
{
	if (!end(&data()->end, &data()->dead))
		return ;
	pthread_mutex_lock(&data()->wrt);
	printf("%zu %d %s\n", (get_time() - data()->start_time), node->id, str);
	pthread_mutex_unlock(&data()->wrt);
}

static int	sleeping_philo(t_philo *node)
{
	if (!end(&data()->end, &data()->dead) || (data()->time_to_sleep >= data()->time_to_die))
		return (1);
	print_status("is sleeping", node);
	ft_usleep(data()->time_to_sleep);
	return (0);
}

static void	eating(t_philo *node)
{
	if (!end(&data()->end, &data()->dead))
		return ;
	pthread_mutex_lock(node->r_fork);
	print_status("has taken a fork", node);
	pthread_mutex_lock(node->l_fork);
	print_status("has taken a fork", node);
	print_status("is eating", node);
	ft_usleep(data()->time_to_eat);
	
	pthread_mutex_lock(&data()->food);
	node->last_meal_time = get_time();
	node->food_eaten++;
	pthread_mutex_unlock(&data()->food);
	
	pthread_mutex_unlock(node->r_fork);
	pthread_mutex_unlock(node->l_fork);
}

void	*routine(void *node)
{
	t_philo	*philo;

	philo = (t_philo *)node;
	if (data()->n_philo == 1)
	{
		print_status("taken rigth fork", philo);
		ft_usleep(data()->time_to_die);
	}
	while (end(&data()->end, &data()->dead))
	{
		if ((philo->id % 2) == 0)
			usleep(100);
		if (data()->food_need != -1 && philo->food_eaten >= data()->food_need)
			break;
		eating(philo);
		if (sleeping_philo(philo))
			break ;
		print_status("is thinking", philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv) || init_struct(argv, argc))
		return (EXIT_FAILURE);
	if (init_philosophers(data()->philos))
		return (EXIT_FAILURE);
	cell_guard();
	quit();
	return (0);
}

// ./philo 1 800 200 200 - Philosopher should not eat and should die.
// ./philo 5 800 200 200 - No Philosopher should die.
// ./philo 5 800 200 200 7 - No Philosopher should die
//  and the simulation should stop when every philosopher 
//  has eaten at least 7 times.
// ./philo 4 410 200 200 - No Philosopher should die.
// ./philo 4 310 200 100 - One Philosopher should die.

// ./philo 4 500 200 2147483647
// ./philo 4 214748364732 200 200