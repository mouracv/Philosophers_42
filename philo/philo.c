/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by aleperei          #+#    #+#             */
/*   Updated: 2024/01/25 18:01:49 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"


// Arguments: 
// number_of_philosophers 
// time_to_die time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]


void *routine()
{
    printf("PRIMEIRA THREAD AQUI \n");
    printf("ACABEI \n");

    printf("SEUGUNDA THREAD AQUI \n");
    printf("ACABEI \n");

    return NULL; 
}

int main(int argc, char **argv)
{
    check_args(argc, argv);
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
