/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:56:52 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/12 15:41:52 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_dine *dine)
{
	int		i;
	t_philo	*temp;

	i = 0;
	temp = dine->philo;
	while (i < dine->philos)
	{
		pthread_join(temp->thread, NULL);
		i++;
		temp = temp->next;
	}
}

void	free_philo(t_philo *philo)
{
	t_philo	*temp;
	t_philo	*next;
	t_philo	*start;

	temp = philo;
	if (temp)
	{
		start = temp;
		while (temp->next != start)
			temp = temp->next;
		temp->next = NULL;
		temp = start;
		while (temp)
		{
			next = temp->next;
			free(temp);
			temp = next;
		}
	}
}

void	clean_restaurants(t_dine *dine)
{
	int	i;

	i = 0;
	if (dine->philo_forks)
	{
		while (i < dine->forks)
		{
			pthread_mutex_destroy(&dine->philo_forks[i]);
			i++;
		}
		free(dine->philo_forks);
	}
	pthread_mutex_destroy(&dine->lock);
	if (dine->philo)
		free_philo(dine->philo);
	free(dine);
}

void	create_threads(t_dine *dine)
{
	int			i;
	t_philo		*temp;
	pthread_t	monitor_thread;
	t_args		*args;

	i = 0;
	pthread_create(&monitor_thread, NULL, monitor, dine);
	temp = dine->philo;
	while (i < dine->philos)
	{
		args = malloc(sizeof(t_args));
		if (!args)
			return ;
		args->dine = dine;
		args->philo = temp;
		pthread_create(&temp->thread, NULL, ft_routine, (void *)args);
		i++;
		temp = temp->next;
	}
	pthread_join(monitor_thread, NULL);
	join_threads(dine);
	if (dine->died && dine->meals != dine->philos)
		printf(WHITE "%ld %ld died\n" RESET, calculate_time(dine),
			dine->philo->id);
	clean_restaurants(dine);
}

int	main(int ac, char **av)
{
	t_dine	*dine;

	if ((ac == 5 || ac == 6) && all_digits(av))
	{
		dine = ft_calloc(1, sizeof(t_dine));
		if (!dine)
			return (1);
		init_arguments(av, dine);
		seating_philosophers(dine);
		gettimeofday(&dine->start, NULL);
		create_threads(dine);
		return (0);
	}
	printf("./philo no_of_philos t_to_die t_to_eat t_to_sleep [no of meals]\n");
}
