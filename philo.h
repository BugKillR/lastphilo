/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:45:30 by kkeskin           #+#    #+#             */
/*   Updated: 2026/03/29 18:43:34 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <pthread.h> // mutex: init destroy lock unlock
//threads: create join detach
# include <limits.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}				t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	int			full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id; // philos are threads
}				t_philo;

typedef struct s_table
{
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_limit_meals;
	int		start_simulation;
	int		end_simulation; // when every philo full or a philo died
	t_fork	*forks;
	t_philo	*philos;
}				t_table;

int	philo(int argc, char *argv[]);
int	atoi_safe(const char *nptr, int *set);
int	ft_isdigit(int c);

#endif