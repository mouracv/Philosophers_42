/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/02 17:33:19 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int    end(pthread_mutex_t *end, int   *status)
{
    int tmp = 0;
    
    pthread_mutex_lock(end);
    tmp = *status;
    pthread_mutex_unlock(end);
    return (tmp);
}

//monitor
//o philo so pode morrer se ficar muito tempo sem comer ou se comer tudo
void    print_status(char *str, t_philo *node)
{
    if (!end(&data()->end, &data()->dead))
        return ;
    
    pthread_mutex_lock(&data()->wrt);
    printf("%zu Philo %d %s\n", (get_time() - data()->start_time), node->id, str);
    // printf("%zu %d %s\n", (get_time() - data()->start_time), node->id, str);
    pthread_mutex_unlock(&data()->wrt);
}

void eating(t_philo *node)
{
    if (!end(&data()->end, &data()->dead))
        return ;
    pthread_mutex_lock(node->r_fork);
    print_status("taken rigth fork", node);
    pthread_mutex_lock(node->l_fork);
    print_status("taken lefth fork", node);
    print_status("is eating", node);
    node->last_meal_time = get_time();
    node->food_eaten++;
    ft_usleep(data()->time_to_eat);
    pthread_mutex_unlock(node->r_fork);
    pthread_mutex_unlock(node->l_fork);
}


void *routine(void  *node)
{
    t_philo *philo = (t_philo *) node;
    
    if (data()->n_philo == 1)
    {
        print_status("taken rigth fork", philo);
        ft_usleep(data()->time_to_die);
    }
    while (end(&data()->end, &data()->dead))
    {
        if ((philo->id % 2) == 0)
            usleep(100);
        
        eating(philo);        
        
        print_status("is sleeping", node);
        ft_usleep(data()->time_to_sleep);
        print_status("is thinking", node);
                
    }
    
    return (NULL); 
}


int main(int argc, char **argv)
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
//  and the simulation should stop when every philosopher has eaten at least 7 times.
// ./philo 4 410 200 200 - No Philosopher should die.
// ./philo 4 310 200 100 - One Philosopher should die.