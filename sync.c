/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 03:57:03 by kkeskin           #+#    #+#             */
/*   Updated: 2026/03/31 04:55:19 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// spinlock to sync philos

void	wait_all_philos(t_table *table)
{
	while (!get_int(&table->table_mutex, &table->all_philos_created))
		;
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
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}
