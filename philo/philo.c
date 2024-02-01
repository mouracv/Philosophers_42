/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/01 16:23:37 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"


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

//monitor
//o philo so pode morrer se ficar muito tempo sem comer ou se comer tudo

void    print_status(char *str, t_philo *node)
{
    pthread_mutex_lock(&data()->wrt);
    printf("%zu Philo %d %s\n", get_time(), node->id, str);
    pthread_mutex_unlock(&data()->wrt);
}

void eating(t_philo *node)
{
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

void go_to_grave(t_philo *node)
{
    int i = 0;

    while (i < data()->n_philo)
    {
        if ((get_time - node[i].last_meal_time) >= data()->time_to_die)
        {
            data()->dead = 0;
            print_status("died in vain", &node[i]);
            break;
        }
        i++;
    }
    return ;
}

int full_philo(t_philo *node)
{
    int times = 0;
    if (data()->food_need < 0)
        return (0);
    while (data()->food_need && node[times].food_eaten >= data()->food_need)
        times++;
    if (times == data()->n_philo)
        return (1);
    
    return (0);
}

void    cell_guard(void)
{
    while (data()->dead)
    {
        if (full_philo(data()->philos))
            break;
        go_to_grave(data()->philos);   
    }
    
}

void *routine(void  *node)
{
    t_philo *philo = (t_philo *) node;
    
    if (data()->n_philo == 1)
    {
        print_status("taken rigth fork", philo);
        ft_usleep(data()->time_to_die);
    }
    while (philo->dead)
    {
        if ((philo->id % 2) == 0)
            usleep(100);
        
        // if (data()->food_need && data()->food_need >= philo->food_eaten)
        // {
        //     /*Deve acabar*/
        // }
        
        eating(philo);
        print_status("is sleeping", node);
        ft_usleep(data()->time_to_sleep);
        print_status("is think", node);
        // ft_usleep(data()->time_to_die);
        
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

    return (0);
}


// ./philo 1 800 200 200 - Philosopher should not eat and should die.
// ./philo 5 800 200 200 - No Philosopher should die.
// ./philo 5 800 200 200 7 - No Philosopher should die
//  and the simulation should stop when every philosopher has eaten at least 7 times.
// ./philo 4 410 200 200 - No Philosopher should die.
// ./philo 4 310 200 100 - One Philosopher should die.