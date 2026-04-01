/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 17:03:16 by kkeskin           #+#    #+#             */
/*   Updated: 2026/04/01 01:48:43 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	length_check(const char *str)
{
	int	i;
	int	digit_count;

	i = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	digit_count = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		digit_count++;
		i++;
	}
	if (digit_count > 10)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	atoi_safe(const char *nptr, int *set)
{
	short int	sign;
	int			res;
	int			i;

	sign = 1;
	res = 0;
	i = 0;
	if (length_check(nptr))
		return (EXIT_FAILURE);
	while (nptr[i] == ' ' || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
		res = (res * 10) + (nptr[i++] - '0');
	res *= sign;
	if (sign == -1 && res >= INT_MIN)
		return (*set = res, EXIT_SUCCESS);
	else if (sign == 1 && res <= INT_MAX)
		return (*set = res, EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	atol_safe(const char *nptr, long *set)
{
	short int	sign;
	long		res;
	int			i;

	sign = 1;
	res = 0;
	i = 0;
	if (length_check(nptr))
		return (EXIT_FAILURE);
	while (nptr[i] == ' ' || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
		res = (res * 10) + (nptr[i++] - '0');
	res *= sign;
	if (sign == -1 && res >= INT_MIN)
		return (*set = res, EXIT_SUCCESS);
	else if (sign == 1 && res <= INT_MAX)
		return (*set = res, EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (status == DIED || !simulation_finished(philo->table))
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-6ld %d is died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

void	print_error(char *message)
{
	printf("%s", message);
}
