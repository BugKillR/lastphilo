/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:33:28 by kijo              #+#    #+#             */
/*   Updated: 2026/04/02 13:31:12 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (0);
	elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (1);
	return (0);
}

void	*observe_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_num, table->philo_num))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_num && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_int(&table->table_mutex, &table->end_simulation, 1);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
