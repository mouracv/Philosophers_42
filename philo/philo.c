/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/15 16:04:38 by aleperei         ###   ########.fr       */
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

		if (eating(philo))
			break;
		if (sleeping_philo(philo))
			break ;
		if (philo_think(philo))
			break;
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


// FALTA CORRIGIR CASO AS FUNCOES DE INICIAR AS STRUCTS NAO FUNCIONAREM
// ./philo 1 800 200 200 - Philosopher should not eat and should die.
// ./philo 5 800 200 200 - No Philosopher should die.
// ./philo 5 800 200 200 7 - No Philosopher should die
//  and the simulation should stop when every philosopher 
//  has eaten at least 7 times.
// ./philo 4 410 200 200 - No Philosopher should die.
// ./philo 4 310 200 100 - One Philosopher should die.

// ./philo 4 500 200 2147483647
// ./philo 4 214748364732 200 200