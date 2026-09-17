#include "philo.h"

int	print_action(t_philo *philo, char *msg)
{
    if(simulation_stopped(philo->data))
    {
        return(1);
    }
	pthread_mutex_lock(&philo->data->printer);
    if(simulation_stopped(philo->data))
    {
	    pthread_mutex_unlock(&philo->data->printer);        
        return(1);        
    }
	printf("%ld %d %s\n", get_time_ms() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->printer);
    return (0);
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
    pthread_mutex_destroy(&data->meals_eaten_mutex);    
    pthread_mutex_destroy(&data->printer);
    pthread_mutex_destroy(&data->is_stopped);
}
