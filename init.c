/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 23:23:50 by kkeskin           #+#    #+#             */
/*   Updated: 2026/03/31 04:56:16 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_id)
{
	int	philo_num;

	philo_num = philo->table->philo_num;
	philo->right_fork = &forks[(philo_id + 1) % philo_num];
	philo->left_fork = &forks[philo_id];
	if (philo_id % 2)
	{
		philo->right_fork = &forks[philo_id];
		philo->left_fork = &forks[(philo_id + 1) % philo_num];
	}
}

static void	philo_init(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

int	init_program(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = 0;
	table->all_philos_created = 0;
	if (safe_malloc(sizeof(t_philo) * table->philo_num,
			(void **)&table->philos))
		return (EXIT_FAILURE);
	safe_mutex_handle(&table->table_mutex, INIT);
	if (safe_malloc(sizeof(t_fork) * table->philo_num,
			(void **)&table->forks))
		return (EXIT_FAILURE);
	while (++i < table->philo_num)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	return (EXIT_SUCCESS);
}
