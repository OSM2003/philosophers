/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:34:49 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/12 15:42:34 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one_philo(t_dine *dine, t_philo *philo)
{
	pthread_mutex_lock(&dine->lock);
	printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine),
		philo->id);
	usleep(dine->time_to_die * 1000);
	dine->died = 1;
	pthread_mutex_unlock(&dine->lock);
}

void	phlio_loop(t_dine *dine, t_philo *philo)
{
	while (1)
	{
		if (check_stop(dine))
			break ;
		eating(dine, philo);
		if (check_stop(dine))
			break ;
		ft_sleep(dine, philo);
		if (check_stop(dine))
			break ;
		ft_think(dine, philo);
		if (check_stop(dine))
			break ;
	}
}
