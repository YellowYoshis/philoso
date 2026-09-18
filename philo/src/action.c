#include "philo.h"

int	is_thinking(t_philo *philo)
{
	long	think_time;

	if (print_action(philo, "is thinking"))
		return (1);
	if (philo->data->philo_nbr % 2 == 0)
		return (0);
	think_time = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
	if (think_time > 0)
		usleep(think_time * 1000);
	return (0);
}

int    is_sleeping(t_philo *philo)
{
    if (print_action(philo, "is sleeping"))
    {
        return(1);
    }
    if(simulation_stopped(philo->data))
        return (1);
    usleep(philo->data->time_to_sleep * 1000);
    return (0);
}



int	is_eating(t_philo *philo)
{
	if(fork_management(philo))
        return (1);
    pthread_mutex_lock(&philo->meals);
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&philo->meals);
	if (print_action(philo, "is eating"))
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return (1);
    }
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
    return (0);
}