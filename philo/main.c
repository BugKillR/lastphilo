/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 16:44:10 by kkeskin           #+#    #+#             */
/*   Updated: 2026/03/29 23:44:51 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5]

int	main(int argc, char *argv[])
{
	if (philo(argc, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
