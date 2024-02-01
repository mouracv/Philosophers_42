/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:15:55 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/01 16:23:08 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_box;

typedef struct s_philo
{
    int                  id;
    int                  dead;
    // int                 time_to_die;
    int                 food_eaten;
    size_t                 last_meal_time;
    int                 status;
    pthread_mutex_t   *r_fork;
    pthread_mutex_t   *l_fork;
          
    t_box  *data;
}               t_philo;

typedef struct s_box
{
    t_philo     *philos;
    pthread_t   *tid;
    
    int     n_philo;
    int     food_need;
    int     dead;

    size_t  time_to_die;    
    size_t  time_to_eat;    
    size_t  time_to_sleep;    
    size_t  start_time;    

    pthread_mutex_t   *forks;
    pthread_mutex_t   wrt;
    
}               t_box;


t_box   *data(void);

//CHECK ARGUMENTS AND ERROR
void    syntax(int flag);
int     check_args(int ac, char **av);

//INICIATE
int     init_mutex(void);
int     box_memory(void);
int     init_philosophers(t_philo   *node);
int     init_struct(char **argv, int argc);


//MANAGEMENT
void *routine(void *node);


//UTILS
size_t  get_time(void);
int     ft_isdigit(int nb);
void	ft_usleep(size_t time);
int     ft_atoi(const char *nptr);
void    *ft_calloc(size_t n, size_t size);

#endif