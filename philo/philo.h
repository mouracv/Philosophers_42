/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:15:55 by aleperei          #+#    #+#             */
/*   Updated: 2024/02/21 13:00:49 by aleperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				food_eaten;
	size_t			last_meal_time;
	int				status;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;

}					t_philo;

typedef struct s_box
{
	t_philo			*philos;
	pthread_t		*tid;

	int				n_philo;
	int				food_need;
	int				dead;

	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;

	pthread_mutex_t	*forks;
	pthread_mutex_t	wrt;
	pthread_mutex_t	end;
	pthread_mutex_t	meal_eat;
}					t_box;

// CHECK ARGUMENTS AND ERROR
void				syntax(int flag);
int					check_args(int ac, char **av);

// INICIATE
t_box				*data(void);
int					init_philosophers(t_philo *node);
int					init_struct(char **argv, int argc);

// MANAGEMENT
void				cell_guard(void);
void				*routine(void *node);
int					eating(t_philo *node);
int					philo_think(t_philo *node);
int					sleeping_philo(t_philo *node);
void				print_status(char *str, t_philo *node);
int					end(pthread_mutex_t *end, int *status);
void				set_mtx_value(pthread_mutex_t *mtx, int *var,
						int new_value);

// UTILS
size_t				get_time(void);
void				ft_usleep(size_t time);
long				ft_atoi(const char *str);
void				*ft_calloc(size_t n, size_t size);

// FRRE AND DESTROY THREADS
void				quit(void);

#endif