/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 03:46:47 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/09 01:36:59 by oalananz         ###   ########.fr       */
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
    t_args *args = (t_args *)arg;
    t_dine *dine = args->dine;
    t_philo *philo = args->philo;
    
    while (!dine->died)
    {
        pthread_mutex_lock(&dine->lock);
        if (calculate_time(dine) - philo->last_meal > dine->time_to_die
            && dine->meals != dine->philos)
        {
            dine->died = 1;
            printf(BLACK "%ld %ld died\n" RESET, calculate_time(dine), philo->id);
            pthread_mutex_unlock(&dine->lock);
            return NULL;
        }
        pthread_mutex_unlock(&dine->lock);
        usleep(1000);
    }
    return NULL;
}
