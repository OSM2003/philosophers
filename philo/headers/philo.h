/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:57:11 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/09 02:27:40 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
# include <stdatomic.h>
#include <string.h>
# include <sys/time.h>
#include <unistd.h>

typedef struct s_philo {
    long id;
    pthread_t thread;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    long last_meal;
    int flag;
    int meals_eaten;
    int eat_flag;
    struct s_philo *next;
} t_philo;

typedef struct s_dine
{
    pthread_mutex_t lock;
    struct timeval start;
    struct timeval end;
    int forks;
    int philos;
    int died;
    int count;
    int time_to_sleep;
    int time_to_eat;
    int time_to_die;
    int number_of_meals;
    int meals;
    t_philo *philo;
} t_dine;

typedef struct s_args {
    t_dine  *dine;
    t_philo *philo;
} t_args;


void    Seating_philosophers(t_dine *dine);
void    init_arguments(char **av, t_dine *dine);
int     ft_atoi(const char *nptr);
int     all_digits(char **av);
void    *ft_calloc(size_t nmemb, size_t size);
void ft_sleep(t_dine *dine, t_philo *philo);
void ft_think(t_dine *dine, t_philo *philo);
void take_forks(t_dine *dine, t_philo *philo);
long    calculate_time(t_dine *dine);
void *ft_routine(void *arg);
void *monitor(void *arg);



#define BLACK   "\033[7;30m"
#define RED     "\033[7;31m"
#define GREEN   "\033[7;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[7;35m"
#define CYAN    "\033[7;36m"
#define WHITE   "\033[0;37m"
#define RESET   "\033[0m"

#endif