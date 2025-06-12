/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 03:46:47 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/12 15:33:40 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_dine *dine)
{
	pthread_mutex_lock(&dine->lock);
	if (dine->died || dine->meals == dine->philos)
	{
		pthread_mutex_unlock(&dine->lock);
		return (1);
	}
	pthread_mutex_unlock(&dine->lock);
	return (0);
}

long	calculate_time(t_dine *dine)
{
	long			elapsed;
	struct timeval	now;

	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - dine->start.tv_sec) * 1000;
	elapsed += (now.tv_usec - dine->start.tv_usec) / 1000;
	return (elapsed);
}

static void	unlock(t_dine *dine)
{
	dine->died = 1;
	pthread_mutex_unlock(&dine->lock);
}

void	*monitor(void *arg)
{
	t_dine	*dine;
	t_philo	*temp;

	dine = (t_dine *)arg;
	temp = dine->philo;
	while (1)
	{
		pthread_mutex_lock(&dine->lock);
		if (dine->died || dine->meals == dine->philos)
		{
			unlock(dine);
			break ;
		}
		if (calculate_time(dine) - temp->last_meal > dine->time_to_die
			&& dine->meals != dine->philos)
		{
			unlock(dine);
			break ;
		}
		pthread_mutex_unlock(&dine->lock);
		usleep(1000);
		temp = temp->next;
	}
	return (NULL);
}
