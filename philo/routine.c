/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 03:44:36 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/11 21:57:41 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_forks(t_dine *dine, t_philo *philo)
{
    pthread_mutex_lock(&dine->lock);
    if (dine->died) {
        pthread_mutex_unlock(&dine->lock);
        return 1;
    }
    pthread_mutex_unlock(&dine->lock);

    pthread_mutex_lock(philo->left_fork);

    pthread_mutex_lock(&dine->lock);
    if (dine->died) {
        pthread_mutex_unlock(&dine->lock);
        pthread_mutex_unlock(philo->left_fork);
        return 1;
    }
    printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine), philo->id);
    pthread_mutex_unlock(&dine->lock);

    pthread_mutex_lock(philo->right_fork);

    pthread_mutex_lock(&dine->lock);
    if (dine->died) {
        pthread_mutex_unlock(&dine->lock);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return 1;
    }
    printf(GREEN "%ld %ld has taken a fork\n" RESET, calculate_time(dine), philo->id);
    pthread_mutex_unlock(&dine->lock);

    return 0;
}

void untake_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void ft_eat(t_dine *dine)
{
    long start = calculate_time(dine);
    while (calculate_time(dine) - start < dine->time_to_eat && !dine->died)
    {
        usleep(100);
    }
}

void eating (t_dine *dine, t_philo *philo)
{
    if (take_forks(dine, philo))
        return;
    if (dine->died)
    {
        untake_forks(philo);
        return;
    }
    philo->eat_flag = 1;
    pthread_mutex_lock(&dine->lock);
    printf(BLUE "%ld %ld is eating\n" RESET, calculate_time(dine), philo->id);
    philo->flag++;
    philo->meals_eaten++;
    if (philo->meals_eaten == dine->number_of_meals)
        dine->meals++;
    pthread_mutex_unlock(&dine->lock);
    
    ft_eat(dine);
    philo->last_meal = calculate_time(dine) + (dine->time_to_eat * 1000);
    untake_forks(philo);
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
    
    if (philo->id % 2 == 1)
        usleep(100);
    while (!dine->died
        && dine->meals != dine->philos)
    {
        philo->flag = 0;
        philo->eat_flag = 0;
        eating(dine, philo);
        if (!dine->died && philo->flag && dine->meals != dine->philos)
        {
            ft_sleep(dine, philo);
            if (!dine->died && dine->meals != dine->philos)
                ft_think(dine, philo);
        }
    }
    return (NULL);
}
