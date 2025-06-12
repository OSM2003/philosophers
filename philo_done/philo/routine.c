/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 03:44:36 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/12 15:40:55 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_dine *dine)
{
	long	start;

	start = calculate_time(dine);
	while (calculate_time(dine) - start < dine->time_to_eat)
	{
		if (check_stop(dine))
			return ;
		usleep(100);
	}
}

void	eating(t_dine *dine, t_philo *philo)
{
	if (take_forks(dine, philo))
		return ;
	if (check_stop(dine))
	{
		untake_forks(philo);
		return ;
	}
	pthread_mutex_lock(&dine->lock);
	printf(BLUE "%ld %ld is eating\n" RESET, calculate_time(dine), philo->id);
	philo->meals_eaten++;
	if (philo->meals_eaten == dine->number_of_meals)
		dine->meals++;
	pthread_mutex_unlock(&dine->lock);
	philo->last_meal = calculate_time(dine);
	ft_eat(dine);
	untake_forks(philo);
}

void	ft_sleep(t_dine *dine, t_philo *philo)
{
	long	start;

	pthread_mutex_lock(&dine->lock);
	printf(CYAN "%ld %ld is sleeping\n" RESET, calculate_time(dine), philo->id);
	pthread_mutex_unlock(&dine->lock);
	start = calculate_time(dine);
	while (calculate_time(dine) - start < dine->time_to_sleep)
	{
		if (check_stop(dine))
			return ;
		usleep(100);
	}
}

void	ft_think(t_dine *dine, t_philo *philo)
{
	pthread_mutex_lock(&dine->lock);
	printf(MAGENTA "%ld %ld is thinking\n" RESET, calculate_time(dine),
		philo->id);
	pthread_mutex_unlock(&dine->lock);
}

void	*ft_routine(void *arg)
{
	t_args	*args;
	t_dine	*dine;
	t_philo	*philo;

	args = (t_args *)arg;
	dine = args->dine;
	philo = args->philo;
	if (dine->philos == 1)
	{
		handle_one_philo(dine, philo);
		free(args);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	phlio_loop(dine, philo);
	free(args);
	return (NULL);
}
