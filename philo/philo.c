/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/19 17:28:55 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Funcao que  contem a minha struct
t_box	*data(void)
{
	static t_box	geral;

	return (&geral);
}

int	sleeping_philo(t_philo *node)
{
	if (!end(&data()->end, &data()->dead))
		return (1);
	print_status("is sleeping", node);
	ft_usleep(data()->time_to_sleep);
	return (0);
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
	if (!(philo->id % 2))
		ft_usleep(1);
	while (end(&data()->end, &data()->dead))
	{
		eating(philo);
		sleeping_philo(philo);
		philo_think(philo);
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
