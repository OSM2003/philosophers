/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 03:46:47 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/11 21:44:20 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    calculate_time(t_dine *dine)
{
    long elapsed;
    struct timeval now;
    
    gettimeofday(&now, NULL);
    elapsed = (now.tv_sec - dine->start.tv_sec) * 1000;
    elapsed += (now.tv_usec - dine->start.tv_usec) / 1000;      
    
    return (elapsed);
}

void *monitor(void *arg)
{
    t_dine *dine = (t_dine *)arg;
    t_philo *temp = dine->philo;

    while (1)
    {
        pthread_mutex_lock(&dine->lock);
        if (dine->died || dine->meals == dine->philos)
        {
            dine->died = 1;
            pthread_mutex_unlock(&dine->lock);
            break;
        }
        if (calculate_time(dine) - temp->last_meal > dine->time_to_die
            && dine->meals != dine->philos)
        {
            dine->died = 1;
            printf(WHITE "%ld %ld died\n" RESET, calculate_time(dine), temp->id);
            pthread_mutex_unlock(&dine->lock);
            break;
        }
        pthread_mutex_unlock(&dine->lock);
        usleep(1000);
        temp = temp->next;
    }
    free(arg);
    return NULL;
}
