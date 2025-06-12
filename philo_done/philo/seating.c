/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seating.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 20:22:04 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/12 15:41:34 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_node(int id)
{
	t_philo	*new_node;

	new_node = malloc(sizeof(t_philo));
	if (!new_node)
		return (NULL);
	new_node->id = id;
	new_node->thread = 0;
	new_node->left_fork = NULL;
	new_node->right_fork = NULL;
	new_node->last_meal = 0;
	new_node->meals_eaten = 0;
	new_node->next = new_node;
	return (new_node);
}

void	insert_end(t_philo **head, t_philo *new_node)
{
	t_philo	*temp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next != *head)
		temp = temp->next;
	temp->next = new_node;
	new_node->next = *head;
}

void	init_arguments(char **av, t_dine *dine)
{
	dine->philos = ft_atoi(av[1]);
	dine->forks = dine->philos;
	dine->time_to_die = ft_atoi(av[2]);
	dine->time_to_eat = ft_atoi(av[3]);
	dine->time_to_sleep = ft_atoi(av[4]);
	dine->philo_forks = malloc(sizeof(pthread_mutex_t) * dine->forks);
	if (av[5])
		dine->number_of_meals = ft_atoi(av[5]);
	else
		dine->number_of_meals = -1;
	if (!dine->philos || !dine->time_to_die || !dine->time_to_sleep
		|| !dine->time_to_eat || dine->number_of_meals == 0)
	{
		printf("Invalid arguments\n");
		free(dine);
		exit(EXIT_FAILURE);
	}
	if (dine->philos > 0)
		dine->philo = create_node(1);
}

void	init_forks(t_dine *dine)
{
	int	i;

	i = 0;
	while (i < dine->forks)
	{
		pthread_mutex_init(&dine->philo_forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&dine->lock, NULL);
}

void	seating_philosophers(t_dine *dine)
{
	int	i;

	i = 2;
	init_forks(dine);
	while (i <= dine->philos)
	{
		insert_end(&dine->philo, create_node(i));
		i++;
	}
	give_forks(dine);
}
