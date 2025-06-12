/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:19:57 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/12 15:42:27 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks_even(t_dine *dine, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (check_stop(dine))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&dine->lock);
	printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine),
		philo->id);
	pthread_mutex_unlock(&dine->lock);
	pthread_mutex_lock(philo->left_fork);
	if (check_stop(dine))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&dine->lock);
	printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine),
		philo->id);
	pthread_mutex_unlock(&dine->lock);
	return (0);
}

int	take_forks_odd(t_dine *dine, t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_stop(dine))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&dine->lock);
	printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine),
		philo->id);
	pthread_mutex_unlock(&dine->lock);
	pthread_mutex_lock(philo->right_fork);
	if (check_stop(dine))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&dine->lock);
	printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine),
		philo->id);
	pthread_mutex_unlock(&dine->lock);
	return (0);
}

int	take_forks(t_dine *dine, t_philo *philo)
{
	int	status;

	status = 0;
	if (philo->id % 2 == 0)
		status = take_forks_even(dine, philo);
	else
		status = take_forks_odd(dine, philo);
	return (status);
}

void	untake_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	give_forks(t_dine *dine)
{
	int		i;
	t_philo	*temp;

	temp = dine->philo;
	i = 0;
	while (i < dine->philos)
	{
		temp->left_fork = &dine->philo_forks[i];
		temp->right_fork = &dine->philo_forks[(i + 1) % dine->forks];
		i++;
		temp = temp->next;
	}
}
