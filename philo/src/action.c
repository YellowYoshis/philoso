#include "philo.h"

void    is_thinking(t_philo *philo)
{
    print_action(philo, "is thinking");
}

void    is_sleeping(t_philo *philo)
{
 //   print_action(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
}

void    fork_management(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        printf("%ld %d has taken a fork\n",get_time_ms(), philo->id);
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d has taken a fork\n",get_time_ms(), philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d has taken a fork\n",get_time_ms(), philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("%ld %d has taken a fork\n",get_time_ms(), philo->id);
    }
}

void	is_eating(t_philo *philo)
{
	fork_management(philo);
    pthread_mutex_lock(&philo->meals);
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&philo->meals);
	print_action(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
    print_action(philo, "is sleeping");
//	print_action(philo, "lache la fourchette de droite");    // a enlever
	pthread_mutex_unlock(philo->right_fork);
//	print_action(philo, "lache la fourchette de gauche"); // a enlever
	pthread_mutex_unlock(philo->left_fork);
}