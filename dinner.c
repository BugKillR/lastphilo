/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:00:21 by kkeskin           #+#    #+#             */
/*   Updated: 2026/04/02 13:27:05 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	if (philo->table->philo_num % 2 == 0)
		return ;
	write_status(THINKING, philo);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->right_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&philo->left_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	better_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->num_limit_meals > 0
		&& philo->meals_counter == philo->table->num_limit_meals)
		set_int(&philo->philo_mutex, &philo->full, 1);
	safe_mutex_handle(&philo->right_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->left_fork->fork, UNLOCK);
}

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_int(&philo->table->table_mutex,
		&philo->table->threads_running_num);
	de_synchronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		better_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

static void	*single_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_int(&philo->table->table_mutex,
		&philo->table->threads_running_num);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->num_limit_meals == 0)
		return ;
	else if (table->philo_num == 1)
		safe_thread_handle(&table->philos[0].thread_id,
			single_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_num)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->observer,
		observe_dinner, table, CREATE);
	table->start_simulation = get_time(MILLISECOND);
	set_int(&table->table_mutex, &table->all_philos_created, 1);
	i = -1;
	while (++i < table->philo_num)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_int(&table->table_mutex, &table->end_simulation, 1);
	safe_thread_handle(&table->observer, NULL, NULL, JOIN);
}
