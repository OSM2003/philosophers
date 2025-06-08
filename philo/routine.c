/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 03:44:36 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/08 03:46:30 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_forks(t_dine *dine, t_philo *philo)
{
    if (!dine->died)
    {
        if (philo->id % 2 == 0 && dine->forks >= 2 && !dine->died) 
        {
            philo->eat_flag=1;
            pthread_mutex_lock(&philo->left_fork);
            pthread_mutex_lock(&dine->lock);
            printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine), philo->id);
            pthread_mutex_unlock(&dine->lock);
            
            pthread_mutex_lock(&philo->right_fork);
            pthread_mutex_lock(&dine->lock);
            printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine), philo->id);
            pthread_mutex_unlock(&dine->lock);
            dine->forks -=2;
        }
        else if(dine->forks >= 2 && !dine->died)
        {
            philo->eat_flag=1;
            pthread_mutex_lock(&philo->right_fork);
            pthread_mutex_lock(&dine->lock);
            printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine), philo->id);
            pthread_mutex_unlock(&dine->lock);
            
            pthread_mutex_lock(&philo->left_fork);
            pthread_mutex_lock(&dine->lock);
            printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine), philo->id);
            pthread_mutex_unlock(&dine->lock);
            dine->forks -=2;
        }
        if(philo->eat_flag == 1 && !dine->died)
        {
            pthread_mutex_lock(&dine->lock);
            printf(RED "%ld %ld is eating\n" RESET, calculate_time(dine), philo->id);
            philo->last_meal = calculate_time(dine);
            philo->flag++;
            philo->meals_eaten++;
            pthread_mutex_unlock(&dine->lock);
            usleep(dine->time_to_eat * 1000);
            dine->forks +=2;
            pthread_mutex_unlock(&philo->left_fork);
            pthread_mutex_unlock(&philo->right_fork);   
        }
    }
}

void ft_sleep(t_dine *dine, t_philo *philo)
{
    pthread_mutex_lock(&dine->lock);
    printf(CYAN "%ld %ld is sleeping\n" RESET, calculate_time(dine), philo->id);
    pthread_mutex_unlock(&dine->lock);
    
    long start = calculate_time(dine);
    while (calculate_time(dine) - start < dine->time_to_sleep && !dine->died)
    {
        usleep(100);
    }
}

void ft_think(t_dine *dine, t_philo *philo)
{
    pthread_mutex_lock(&dine->lock);
    printf(MAGENTA "%ld %ld is thinking\n" RESET, calculate_time(dine), philo->id);
    pthread_mutex_unlock(&dine->lock);
}

void *ft_routine(void *arg)
{
    t_args *args = (t_args *)arg;
    t_dine *dine = args->dine;
    t_philo *philo = args->philo;
    
    pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitor, arg);

    if (philo->id % 2 == 0)
        usleep(100); 
    while (!dine->died)
    {
        philo->flag = 0;
        philo->eat_flag = 0;
        take_forks(dine, philo);
        if (!dine->died && philo->flag)
        {
            ft_sleep(dine, philo);
            if (!dine->died)
                ft_think(dine, philo);
        }
    }
    pthread_join(monitor_thread, NULL);
    return (NULL);
}
