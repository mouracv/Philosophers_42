/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by aleperei          #+#    #+#             */
/*   Updated: 2024/01/31 16:34:33 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"



t_box  *data(void)
{
    static t_box geral;
    
    return (&geral);
}

size_t	ft_usleep(size_t time)
{
	size_t	start;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}

void    clear_mutex(void)
{
    int i = 0;
    
    while (++i < data()->n_philo)
        pthread_mutex_destroy(&data()->forks[i]);
    
    pthread_mutex_destroy(&data()->wrt);
    
}


void    quit(void)
{
    clear_mutex();
    if (data()->philos)
        free(data()->philos);
    if (data()->forks)
        free(data()->forks);
    if (data()->tid)
        free(data()->tid);
}


void *routine(void  *node)
{
    t_philo *philo = (t_philo *) node;
    
    /*TRABALHAR*/

    return NULL; 
}





int main(int argc, char **argv)
{
    if (check_args(argc, argv) || init_struct(argv, argc))
        return (EXIT_FAILURE); 
    if (1)
    {
        /* code */
    }
    
    // pthread_mutex_init();
    // if (argc != 5 || argc != 6)
    //     return(syntax(), 0);
    // int i = 130;
    // pthread_t id1, id2;

    // pthread_create(&id1, NULL, &routine, NULL);
    // i = 127;
    // pthread_create(&id2, NULL, &routine, NULL);
    
    // pthread_join(id1, NULL);    
    // pthread_join(id2, NULL);    
    

    return (0);
}


// ./philo 1 800 200 200 - Philosopher should not eat and should die.
// ./philo 5 800 200 200 - No Philosopher should die.
// ./philo 5 800 200 200 7 - No Philosopher should die
//  and the simulation should stop when every philosopher has eaten at least 7 times.
// ./philo 4 410 200 200 - No Philosopher should die.
// ./philo 4 310 200 100 - One Philosopher should die.