/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:15:55 by aleperei          #+#    #+#             */
/*   Updated: 2024/01/29 16:37:28 by aleperei         ###   ########.fr       */
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
    
    int                 last_meal_time;
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

    size_t  time_to_die;    
    size_t  time_to_eat;    
    size_t  time_to_sleep;    
    size_t  start_time;    

    pthread_mutex_t   *forks;
    
}               t_box;


int check_args(int ac, char **av);
int	ft_atoi(const char *nptr);
int	ft_isdigit(int nb);
void	syntax(int flag);
void	*ft_calloc(size_t n, size_t size);
t_box  *data(void);




#endif