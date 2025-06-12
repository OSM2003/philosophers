/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalananz <oalananz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:57:11 by oalananz          #+#    #+#             */
/*   Updated: 2025/06/12 15:41:57 by oalananz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	long			id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	int				flag;
	int				meals_eaten;
	struct s_philo	*next;
}					t_philo;

typedef struct s_dine
{
	pthread_mutex_t	lock;
	pthread_mutex_t	*philo_forks;
	struct timeval	start;
	struct timeval	end;
	int				forks;
	int				philos;
	int				died;
	int				count;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				number_of_meals;
	int				meals;
	t_philo			*philo;
}					t_dine;

typedef struct s_args
{
	t_dine			*dine;
	t_philo			*philo;
}					t_args;

void				seating_philosophers(t_dine *dine);
void				init_arguments(char **av, t_dine *dine);
int					ft_atoi(const char *nptr);
int					all_digits(char **av);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_sleep(t_dine *dine, t_philo *philo);
void				ft_think(t_dine *dine, t_philo *philo);
int					take_forks(t_dine *dine, t_philo *philo);
long				calculate_time(t_dine *dine);
void				*ft_routine(void *arg);
void				*monitor(void *arg);
int					check_stop(t_dine *dine);
void				give_forks(t_dine *dine);
void				untake_forks(t_philo *philo);
void				phlio_loop(t_dine *dine, t_philo *philo);
void				handle_one_philo(t_dine *dine, t_philo *philo);
void				eating(t_dine *dine, t_philo *philo);

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

#endif