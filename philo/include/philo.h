#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

typedef struct s_data t_data;

// typedef struct  s_fork
// {
//     pthread_mutex_t fork;
//     int     fork_id;
// }       t_fork;

typedef struct s_philo
{
    int id;
    int full;
    long    meal_counter;
    long    last_meal_time; 
    pthread_t   thread_id;
    pthread_mutex_t meals;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    t_data *data;
}       t_philo;

typedef struct s_data
{
    long    philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    meals_counter;
    long    start_time;
    int     end_simulation;
    pthread_mutex_t     *forks;
    pthread_mutex_t     printer;
    pthread_mutex_t     is_stopped;
    t_philo *philos;
}       t_data;

// UTILS FUNCTIONS

int 	is_digit(char **argv);
void    err_exit(char *error);
void destroy_mutex(t_data *data);
void    ft_cleanup(t_data *data);

// LIB FUNCTIONS

long    ft_atol(char *str);

// PARSING FUNCTIONS

void    parse_input(t_data *data, char **argv);

// DATA INITIALISATION

int    data_init(t_data *data);

// SIMULATION

int simulation_started(t_data *data);

#endif
