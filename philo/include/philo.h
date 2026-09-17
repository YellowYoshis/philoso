#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					full;
	long				meal_counter;
	long				last_meal_time;
	pthread_t			thread_id;
	pthread_mutex_t		meals;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					end_simulation;
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_counter;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		printer;
	pthread_mutex_t		is_stopped;
	t_philo				*philos;
	pthread_t           monitor; // to do init
}						t_data;

// UTILS FUNCTIONS

int						is_digit(char **argv);
void					destroy_mutex(t_data *data);
void					ft_cleanup(t_data *data);
int					print_action(t_philo *philo, char *msg);
long					get_time_ms(void);

// LIB FUNCTIONS

long					ft_atol(char *str);

// PARSING FUNCTIONS

int						parse_input(t_data *data, char **argv);

// DATA INITIALISATION

int						data_init(t_data *data);

// SIMULATION

int						simulation_started(t_data *data);
void					stop_simulation(t_data *data);
int						simulation_stopped(t_data *data);
int					is_eating(t_philo *philo);
int					is_sleeping(t_philo *philo);
int					is_thinking(t_philo *philo);

#endif

/*
	data race
*/