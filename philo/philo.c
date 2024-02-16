/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/16 17:03:01 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Funcao que  contem a minha struct
t_box	*data(void)
{
	static t_box	geral;

	return (&geral);
}

void	*routine(void *node)
{
	t_philo	*philo;

	philo = (t_philo *)node;
	if (data()->n_philo == 1)
	{
		print_status("has taken a fork", philo);
		ft_usleep(data()->time_to_die);
	}
	while (end(&data()->end, &data()->dead))
	{
		if ((data()->n_philo % 2))
		{
			if (philo->id == data()->n_philo)
			{
				usleep(data()->time_to_eat / 2);
			}
			else
				usleep(100);
		}
		else
		{
			if ((philo->id % 2))
				usleep(100);
		}
		
		if (eating(philo))
			break ;
		if (sleeping_philo(philo))
			break ;
		if (philo_think(philo))
			break ;
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