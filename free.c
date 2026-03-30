/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 04:46:36 by kkeskin           #+#    #+#             */
/*   Updated: 2026/03/30 04:48:17 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_thread_mutex(t_table *table)
{
	if (table->philos)
		free(table->philo_num);
	if (table->forks)
		free(table->forks);
}
