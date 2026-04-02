/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 03:57:03 by kkeskin           #+#    #+#             */
/*   Updated: 2026/04/02 13:48:29 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// spinlock to sync philos

void	wait_all_philos(t_table *table)
{
	while (!get_int(&table->table_mutex, &table->all_philos_created))
		usleep(100);
}

void	better_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
			usleep(100);
	}
}

int	all_threads_running(t_mutex *mutex, int *threads, int philo_num)
{
	int	ret;

	ret = 0;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_num)
		ret = 1;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	increase_int(t_mutex *mutex, int *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->philo_num % 2 == 0)
	{
		if (philo->id % 2 == 0)
			better_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
		{
			thinking(philo);
			better_usleep(1e3, philo->table);
		}
	}
}
