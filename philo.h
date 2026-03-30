/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:45:30 by kkeskin           #+#    #+#             */
/*   Updated: 2026/03/30 04:50:05 by kkeskin          ###   ########.fr       */
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
# include <limits.h> // to use INT_MIN && INT_MAX
# include <errno.h> // for error macros

// Enums
typedef enum e_operations
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}				t_opeartions;

typedef pthread_mutex_t	t_mutex;

// Structs

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
	t_table		*table;
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

// Core

int		init_program(t_table *table);
int		philo(int argc, char *argv[]);

// Utils

int		atoi_safe(const char *nptr, int *set);
int		ft_isdigit(int c);
void	print_error(char *message);

// Wrappers

int		safe_malloc(size_t bytes, void *memory);
int		safe_mutex_handle(t_mutex *mutex, t_opeartions op);
int		safe_thread_handle(pthread_t *thread, void *(*routine)(void *),
			void *data, t_opeartions op);

#endif