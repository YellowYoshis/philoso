#include "philo.h"

int    is_thinking(t_philo *philo)
{
    if(print_action(philo, "is thinking"))
        return (1);
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

int    fork_management(t_philo *philo)
{
    if (philo->data->philo_nbr == 1)
    {
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
        while(!simulation_stopped(philo->data))
            ;
        pthread_mutex_unlock(philo->right_fork);
        return (1);
    }
    if (philo->id % 2 == 0)
    {
        if (simulation_stopped(philo->data))
            return (1);
        pthread_mutex_lock(philo->right_fork);
        if(print_action(philo, "has taken a fork"))
        {
            pthread_mutex_unlock(philo->right_fork);            
            return (1);
        }
        pthread_mutex_lock(philo->left_fork);
        if(print_action(philo, "has taken a fork"))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);       
            return (1);
        }
    }
    else
    {
        if (simulation_stopped(philo->data))
            return (1);
        pthread_mutex_lock(philo->left_fork);
        if(print_action(philo, "has taken a fork"))
        {
            pthread_mutex_unlock(philo->left_fork);            
            return (1);
        }
        pthread_mutex_lock(philo->right_fork);
        if(print_action(philo, "has taken a fork"))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);       
            return (1);
        }
    }
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