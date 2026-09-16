#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->printer);
	printf("%ld %d %s\n", get_time_ms(), philo->id, msg);
	pthread_mutex_unlock(&philo->data->printer);
}

void destroy_mutex(t_data *data)
{
    int i;
    long len;

    i = 0;
    len = data->philo_nbr;
    while(i < len)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i].meals);
        i++;
    }
    pthread_mutex_destroy(&data->printer);
    pthread_mutex_destroy(&data->is_stopped);
}

