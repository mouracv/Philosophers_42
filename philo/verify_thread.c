/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:03:47 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/02 17:36:13 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void    clear_mutex(void)
{
    int i = 0;
    
    while (++i < data()->n_philo)
        pthread_mutex_destroy(&data()->forks[i]);
    
    pthread_mutex_destroy(&data()->wrt);
    pthread_mutex_destroy(&data()->end);
    
}

void    quit(void)
{
    int  i = -1;

    while (++i < data()->n_philo)
        pthread_join(data()->tid[i], NULL);
        
    clear_mutex();
    if (data()->philos)
        free(data()->philos);
    if (data()->forks)
        free(data()->forks);
    if (data()->tid)
        free(data()->tid);
}

void go_to_grave(t_philo *node)
{
    int i = 0;

    while (i < data()->n_philo)
    {
        if ((get_time() - node[i].last_meal_time) >= data()->time_to_die)
        {
            printf("\033[0;31m OLA\n \033[0m");
            data()->dead = 0;
            pthread_mutex_lock(&data()->wrt);
            printf("%zu Philo %d %s\n", (get_time() - data()->start_time), node->id, "died in vain");
            pthread_mutex_unlock(&data()->wrt);
            break;
        }
        i++;
    }
    return ;
}

int full_philo(t_philo *node)
{
    int i = 0;
    int times = 0;
    
    if (data()->food_need < 0)
        return (0);
    while (data()->food_need && i < data()->n_philo && node[i].food_eaten >= data()->food_need)
    {
        times++;
        i++;
    }
    if ((times) == data()->n_philo)
    {
        data()->dead = 0;
        return (1);
    }
    return (0);
}

void    cell_guard(void)
{
    while (end(&data()->end, &data()->dead))
    {
        full_philo(data()->philos);
        if (!end(&data()->end, &data()->dead))
            break;
        go_to_grave(data()->philos);   
    }
}
