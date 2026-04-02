/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:45:30 by kkeskin           #+#    #+#             */
/*   Updated: 2026/04/02 13:10:08 by kkeskin          ###   ########.fr       */
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

typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}				t_time;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}				t_status;

typedef pthread_mutex_t	t_mutex;

typedef struct s_table	t_table;

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
	t_mutex		philo_mutex; // to avoid races with monitor
}				t_philo;

typedef struct s_table
{
	int			philo_num;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			num_limit_meals;
	long		start_simulation; // when sim started
	int			end_simulation; // when every philo full or a philo died
	int			all_philos_created; // when all philos malloced,to sync philos
	int			threads_running_num;
	pthread_t	observer;
	t_mutex		table_mutex;
	t_mutex		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}				t_table;

// Core

int		init_program(t_table *table);
int		philo(int argc, char *argv[]);
void	start_dinner(t_table *table);
void	thinking(t_philo *philo);

// Observer

void	*observe_dinner(void *data);

// Utils

int		atoi_safe(const char *nptr, int *set);
int		atol_safe(const char *nptr, long *set);
int		ft_isdigit(int c);
void	write_status(t_status status, t_philo *philo);
void	print_error(char *message);

// Wrappers

int		safe_malloc(size_t bytes, void **memory);
int		safe_mutex_handle(t_mutex *mutex, t_opeartions op);
int		safe_thread_handle(pthread_t *thread, void *(*routine)(void *),
			void *data, t_opeartions op);

// Get-Set

void	set_int(t_mutex *mutex, int *dest, int value);
int		get_int(t_mutex *mutex, int *value);
void	set_long(t_mutex *mutex, long *dest, long value);
long	get_long(t_mutex *mutex, long *value);
int		simulation_finished(t_table *table);

// Sync

long	get_time(t_time time_code);
void	wait_all_philos(t_table *table);
void	better_usleep(long usec, t_table *table);
void	increase_int(t_mutex *mutex, int *value);
int		all_threads_running(t_mutex *mutex, int *threads, int philo_num);
void	de_synchronize_philos(t_philo *philo);

// Free

void	free_thread_mutex(t_table *table);

#endif