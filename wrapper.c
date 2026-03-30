/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkeskin <kkeskin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 23:44:23 by kkeskin           #+#    #+#             */
/*   Updated: 2026/03/30 05:06:38 by kkeskin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_malloc(size_t bytes, void *memory)
{
	memory = malloc(bytes);
	if (memory == NULL)
	{
		print_error("Error occured on malloc!\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	handle_mutex_error(int status, t_opeartions op)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == op || UNLOCK == op))
		print_error("The value specified by mutex is invalid!\n");
	else if (EINVAL == status && INIT == op)
		print_error("The value specified by attr is invalid!\n");
	else if (EDEADLK == status)
		print_error("A deadlock would occur if the "
			"thread blocked waiting for mutex!\n");
	else if (EPERM == status)
		print_error("The current thread does not hold a lock on mutex!\n");
	else if (ENOMEM == status)
		print_error("The process cannot allocate enough memory to "
			"create another mutex!\n");
	else if (EBUSY == status)
		print_error("Mutex is locked.\n");
}

int	safe_mutex_handle(t_mutex *mutex, t_opeartions op)
{
	if (LOCK == op)
		handle_mutex_error(pthread_mutex_lock(mutex), op);
	else if (UNLOCK == op)
		handle_mutex_error(pthread_mutex_unlock(mutex), op);
	else if (INIT == op)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), op);
	else if (DESTROY == op)
		handle_mutex_error(pthread_mutex_destroy(mutex), op);
	else
	{
		print_error("Wrong op code for mutex handle!\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	handle_thread_error(int status, t_opeartions op)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		print_error("No resources to create anoter thread!\n");
	else if (EPERM == status)
		print_error("The caller does not have appropriate permission!\n");
	else if (EINVAL == status && CREATE == op)
		print_error("The value specified by attr is invalid!\n");
	else if (EINVAL == status && (JOIN == op || DETACH == op))
		print_error("The value specified by thread is not joinable!\n");
	else if (ESRCH == status)
		print_error("No thread could be found corresponding to that"
			" specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		print_error("A deadlock was detected or the value of"
			" thread specifies the calling thread!\n");
}

int	safe_thread_handle(pthread_t *thread, void *(*routine)(void *),
						void *data, t_opeartions op)
{
	if (CREATE == op)
		handle_thread_error(pthread_create(thread, NULL, routine, data), op);
	else if (JOIN == op)
		handle_thread_error(pthread_join(*thread, NULL), op);
	else if (DETACH == op)
		handle_thread_error(pthread_detach(*thread), op);
	else
	{
		print_error("Wrong op code for thread_handle: !"
			"use <CREATE> <JOIN> <DETACH>\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
