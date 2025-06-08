/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seating.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 20:22:04 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/09 02:50:01 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *create_node(int id)
{
    t_philo *new_node = malloc(sizeof(t_philo));
    if (!new_node)
        return NULL;
    new_node->id = id;
    new_node->thread = 0;
    new_node->last_meal = 0;
    new_node->meals_eaten = 0;
    new_node->eat_flag = 0;
    new_node->next = new_node;
    return new_node;
}

void insert_end(t_philo **head, t_philo *new_node) {
    if (!*head) {
        *head = new_node;
        return;
    }
    t_philo *temp = *head;
    while (temp->next != *head)
        temp = temp->next;
    temp->next = new_node;
    new_node->next = *head;
}

void    init_arguments(char **av, t_dine *dine)
{
    dine->philos = ft_atoi(av[1]);
    dine->forks = dine->philos;
    dine->time_to_die = ft_atoi(av[2]);
    dine->time_to_eat = ft_atoi(av[3]);
    dine->time_to_sleep = ft_atoi(av[4]);
    if(av[5])
        dine->number_of_meals = ft_atoi(av[5]);
    else
        dine->number_of_meals = -1;
    if(!dine->philos || !dine->time_to_die
        || !dine->time_to_sleep || !dine->time_to_eat)
    {
        free(dine);
        exit(EXIT_FAILURE);
    }
    if(dine->philos > 0)
        dine->philo = create_node(1);
}

void    Seating_philosophers(t_dine *dine)
{
    int i;
    
    i = 2;
    while( i <= dine->philos)
    {
        insert_end(&dine->philo,create_node(i));
        i++;
    }
}

// void display(t_philo *head) {
//     if (!head)
//         return;
//     t_philo *temp = head;
//     do {
//         printf("Philosopher %ld\n", temp->id);
//         temp = temp->next;
//     } while (temp != head);
// }
