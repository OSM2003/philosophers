/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:56:52 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/07 22:31:19 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void display_dine(t_dine *dine)
{
    printf("------ Dine Struct Info ------\n");
    printf("Number of philosophers   : %d\n", dine->philos);
    printf("Number of forks          : %d\n", dine->forks);
    printf("Time to die (ms)         : %d\n", dine->time_to_die);
    printf("Time to eat (ms)         : %d\n", dine->time_to_eat);
    printf("Time to sleep (ms)       : %d\n", dine->time_to_sleep);
    printf("Meals per philosopher    : %d\n", dine->number_of_meals);
    printf("Start time (s:us)        : %ld : %ld\n", dine->start.tv_sec, dine->start.tv_usec);
    printf("End time   (s:us)        : %ld : %ld\n", dine->end.tv_sec, dine->end.tv_usec);
    printf("-------------------------------\n");
}

void    *ft_eat(void *arg)
{
    t_args *args = (t_args *)arg;
    t_dine *dine = args->dine;
    t_philo *philo = args->philo;
    long elapsed;

    pthread_mutex_lock(&dine->lock);
    gettimeofday(&dine->end, NULL);
    elapsed = (dine->end.tv_sec - dine->start.tv_sec) * 1000;
    elapsed += (dine->end.tv_usec - dine->start.tv_usec) / 1000;
    printf(YELLOW "%ld %ld is eating\n" RESET,elapsed, philo->id);
    usleep(dine->time_to_eat * 1000);
    pthread_mutex_unlock(&dine->lock);

    return NULL;
}

void    join_threads(t_dine *dine)
{
    int i;

    i = 0;
    t_philo *temp;

    temp = dine->philo;
    while(i < dine->philos)
    {
        pthread_join(temp->thread,NULL);
        i++;
        temp = temp->next;
    }
}

void    *ft_routine(void *arg)
{
    t_args *args = (t_args *)arg;
    t_dine *dine = args->dine;
    t_philo *philo = args->philo;
    long elapsed;

    pthread_mutex_lock(&dine->lock);
    gettimeofday(&dine->end, NULL);
    elapsed = (dine->end.tv_sec - dine->start.tv_sec) * 1000;
    elapsed += (dine->end.tv_usec - dine->start.tv_usec) / 1000;
    printf(BLUE "%ld %ld is eating\n" RESET,elapsed, philo->id);
    usleep(dine->time_to_eat * 1000);
    printf(CYAN "%ld %ld is sleeping\n" RESET,elapsed, philo->id);
    usleep(dine->time_to_sleep);
    printf(MAGENTA "%ld %ld is thinking\n" RESET,elapsed, philo->id);
    pthread_mutex_unlock(&dine->lock);

    return (NULL);
}

void    create_threads(t_dine *dine)
{
    int i = 0;
    t_philo *temp = dine->philo;
    display_dine(dine);
    
    while(i < dine->philos)
    {
        t_args *args = malloc(sizeof(t_args));
        args->dine = dine;
        args->philo = temp;
        usleep(10000);
        pthread_create(&temp->thread, NULL, ft_routine, (void *)args);
        i++;
        temp = temp->next;
    }
    join_threads(dine);
}

int main(int ac, char **av)
{
    printf("%d\n",all_digits(av));
    if((ac == 5 || ac == 6) && all_digits(av))
    {
        t_dine *dine;

        dine = ft_calloc(1,sizeof(t_dine));
        if(!dine)
            return (1);
        init_arguments(av,dine);
        Seating_philosophers(dine);
        gettimeofday(&dine->start, NULL);
        // display(dine->philo);
        create_threads(dine);
        return 0;
    }
    printf(RED "./phio number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}
