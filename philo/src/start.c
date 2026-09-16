#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void    penser(t_philo *philo)
{
    printf("philo %d pense ...\n", philo->id);
}

void    dormir(t_philo *philo)
{
    printf("philo %d dort ...\n", philo->id);
    usleep(philo->data->time_to_sleep * 1000);
}

void    fork_management(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        printf("philo %d prend la fourchette de droite\n", philo->id);
        pthread_mutex_lock(philo->left_fork);
        printf("philo %d prend la fourchette de gauche\n", philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        printf("philo %d prend la fourchette de gauche\n", philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("philo %d prend la fourchette de droite\n", philo->id);
    }
}

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->printer);
	printf("philo %d %s\n", philo->id, msg);
	pthread_mutex_unlock(&philo->data->printer);
}

void	manger(t_philo *philo)
{
	fork_management(philo);
    pthread_mutex_lock(&philo->meals);
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&philo->meals);
	print_action(philo, "mange ...");
	usleep(philo->data->time_to_eat * 1000);
	print_action(philo, "lache la fourchette de droite");    
	pthread_mutex_unlock(philo->right_fork);
	print_action(philo, "lache la fourchette de gauche");
	pthread_mutex_unlock(philo->left_fork);
}

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->is_stopped);
	data->end_simulation = 1;
	pthread_mutex_unlock(&data->is_stopped);
}

int	simulation_stopped(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->is_stopped);
	stop = data->end_simulation;
	pthread_mutex_unlock(&data->is_stopped);
	return (stop);
}

void *simulation(void *arg)
{
    t_philo     *philo;

    philo = (t_philo *)arg;
    while(!simulation_stopped(philo->data))
    {
        manger(philo);
        dormir(philo);
        penser(philo);
    }
    return (NULL);
}

int simulation_started(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_time_ms();
    while(i < data->philo_nbr)
    {
        data->philos[i].last_meal_time = data->start_time;
        if(pthread_create(&data->philos[i].thread_id, NULL, simulation, &data->philos[i]))
            return (1);   
        i++;
    }
    i = 0;
    while(i < data->philo_nbr)
    {
        pthread_join(data->philos[i].thread_id, NULL);
        i++;
    }
    return (0);
}