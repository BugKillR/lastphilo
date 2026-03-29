/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:45:08 by kkeskin           #+#    #+#             */
/*   Updated: 2026/03/29 18:52:39 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	error_exit(char *message)
{
	printf("%s", message);
}

static int	argument_control(int argc, char *argv[])
{
	int	i;
	int	num;

	i = 1;
	if (argc < 5 || 6 < argc)
		return (1);
	while (argv[i])
	{
		if (atoi_safe(argv[i], &num))
			return (1);
		i++;
	}
	return (0);
}

static int	parser(int argc, char *argv[], t_table *table)
{
	if (atoi_safe(argv[1], &(*table).philo_num))
		return (EXIT_FAILURE);
	else if (atoi_safe(argv[2], &(*table).time_to_die))
		return (EXIT_FAILURE);
	else if (atoi_safe(argv[3], &(*table).time_to_eat))
		return (EXIT_FAILURE);
	else if (atoi_safe(argv[4], &(*table).time_to_sleep))
		return (EXIT_FAILURE);
	(*table).time_to_die *= 1000;
	(*table).time_to_eat *= 1000;
	(*table).time_to_sleep *= 1000;
	if (argc == 6)
	{
		if (atoi_safe(argv[5], &(*table).num_limit_meals))
			return (EXIT_FAILURE);
	}
	else
		table->num_limit_meals = -1;
	if (table->philo_num <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (EXIT_FAILURE);
	if (argc == 6)
		if (table->num_limit_meals <= 0)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo(int argc, char *argv[])
{
	t_table	table;

	if (argument_control(argc, argv) || parser(argc, argv, &table))
	{
		error_exit("* Enter values higher than 0!\n");
		error_exit("* ./philo number_of_philo time_to_die time_to_eat ");
		error_exit("time_to_sleep [number_of_times_each_philo_must_eat]\n");
		return (EXIT_FAILURE);
	}
	//init_program(&table);
	//start_dinner(&table);
	//clean(&table);
	return (EXIT_SUCCESS);
}
