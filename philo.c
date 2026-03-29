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

static int	argument_control(int argc, char *argv[])
{
	int	i;
	int	k;

	i = 1;
	if (argc < 5 || 6 < argc)
		return (1);
	while (argv[i])
	{
		k = 0;
		while (argv[i][k])
		{
			if (!ft_isdigit(argv[i][k]))
				return (1);
			k++;
		}
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	philo(int argc, char *argv[])
{
	t_table	table;

	if (argument_control(argc, argv))
	{
		write(2, "./philo number_of_philo time_to_die time_to_eat", 48);
		write(2, "time_to_sleep [number_of_times_each_philo_must_eat]\n", 53);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
