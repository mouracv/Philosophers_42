/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by aleperei          #+#    #+#             */
/*   Updated: 2024/01/30 14:12:39 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

//COMMENTS
// Arguments: 
// number_of_philosophers 
// time_to_die time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]


//Let's think to the conditions the inputs has to respect: obviously the input must contain only numbers; the correction sheet, at the moment
//I'm writing this guide (4/11/2022) tells you to test with no more that 200 philos so we can set the limit of philos to 200 and can't be less than 1;
//for what concerns the death, eat and think time the only thing you. 
//have to check is that they are bigger than 0.

// Routine
// The routine will be the function executed over and over by the philos, and is also going to start the supervisor for each philo.
// Basically we have to create a loop that will be interrupted by the death of one of the philos or by reaching the times that each of them 
// must eat, in this loop we'll tell them to: eat, sleep and think. But how? Starting from the thinking action, a philo has to think whenever he can't eat so
// it's pretty simple we just have to insert the message "Philo x is thinking". Moving on we have the eating action
// this one is going to be divided in four main actions: picking the two forks needed, eating, dropping the forks and sleeping (you can also make sleeping action apart).
// Let's start with the forks picking, this is pretty simple, a philo to pick a fork locks the mutex refered to it so we are going to use the pthread_mutex_lock function.
// Note that if you consider the philos disposed clockwise you are going to lock the right fork before the left one
// if you consider them disposed counterclockwise then you are going to lock the left one first.
// Now that the philo has taken the forks he need to eat and here we update the status(to do that I've made an int inside the philo struct) of the philo so that the supervisor will know that he's eating and he don't have to die, and then we simply use an usleep 
// (i suggest you to recode it by your self for making it faster, you can find mine in src/utils/utils.c). Right after that, before dropping the forks, we update the philo status.
// At this point the philo have to drop the froks, we replicate the pick fork function but this time we use the function pthread_muted_unlock to unlock the mutexes previously locked.
// At this point we make the philo sleep using another time the usleep function.


//Devolve o tempo em milisegundos
size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


int     init_philosophers(t_philo   *node)
{
    int i = 1;
    
    node[0].status = 0;
    node[0].last_meal_time = 0;
    node[0].r_fork = &data()->forks[0];
    node[0].r_fork = &data()->forks[data()->n_philo - 1];
    while (i < data()->n_philo)
    {
        node[i].status = 0;
        node[i].last_meal_time = 0;
        node[i].r_fork = &data()->forks[i];
        node[i].r_fork = &data()->forks[data()->n_philo - 1];
    }
}




int box_memore(void)
{
    data()->forks = ft_calloc(data()->n_philo, sizeof(pthread_mutex_t));
    if (!data()->forks)
        return (syntax(5), 1);
    data()->philos = ft_calloc(data()->n_philo, sizeof(t_philo));
    if (!data()->forks)
        return (free(data()->forks), syntax(5), 1);
    data()->tid = ft_calloc(data()->n_philo, sizeof(pthread_t));
    if (!data()->tid)
        return (free(data()->forks), free(data()->philos), syntax(5), 1);
    
    return (0);
}

int    init_struct(char **argv, int argc)
{
    data()->n_philo = ft_atoi(argv[1]);
    if (data()->n_philo > 200)
        return (syntax(3), 1);
    data()->time_to_die = (size_t) ft_atoi(argv[2]);
    data()->time_to_eat = (size_t) ft_atoi(argv[3]);
    data()->time_to_sleep = (size_t) ft_atoi(argv[4]);
    data()->start_time = get_time();
    if (data()->n_philo <= 0 || !data()->time_to_die || !data()->time_to_eat || !data()->time_to_sleep)
        return (syntax(4), 1);
    if (argv == 6)
        data()->food_need = ft_atoi(argv[5]);
    else
        data()->food_need = -1;
    if (box_memore())
        return (1);
    return (0);
}



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