#include "philo.h"

void *simulation(void *arg)
{
    t_philo     *philo;

    philo = (t_philo *)arg;
    while (get_time_ms() < philo->data->start_time)
    ;
    while(!simulation_stopped(philo->data))
    {
        if(is_eating(philo))
            return (NULL);
        if (philo->meal_counter > 0)
        {
            pthread_mutex_lock(&philo->meals);        
            philo->meal_counter--;
			pthread_mutex_unlock(&philo->meals);
        }
        if (philo->meal_counter == 0)
        {
            pthread_mutex_lock(&philo->meals);
            philo->data->meal_eaten++;
            pthread_mutex_unlock(&philo->meals); //proteger
            print_action(philo, "done eating");
            return (NULL);
        }
        if (is_sleeping(philo))
            return (NULL);
        if (is_thinking(philo))
            return (NULL);
    }
    return (NULL);
}

void    *simulation_monitor(void *arg)
{
    t_data     *data;
    int     i;
    long	last_meal;

    last_meal = 0;
    i = 0;
    data = (t_data *)arg;
    while (get_time_ms() < data->start_time)
    ;
    while (!simulation_stopped(data))
    {
        i = 0;
        while (i < data->philo_nbr)
        {
            if (data->meal_eaten == data->philo_nbr)
                return (NULL);
            if (get_time_ms() - last_meal  >= data->time_to_die)
            {
                if (data->meal_eaten == data->philo_nbr)
                    return (NULL);
                print_action(&data->philos[i], "is dead");
                stop_simulation(data);
                return (NULL);    
            }
            i++;
        }
    }
    return (NULL);
}

int simulation_started(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_time_ms() + 800;
    while(i < data->philo_nbr)
    {
        data->philos[i].last_meal_time = data->start_time;
        if(pthread_create(&data->philos[i].thread_id, NULL, simulation, &data->philos[i]))
            return (1);   
        i++;
    }
    if (pthread_create(&data->monitor, NULL, simulation_monitor, data))
        return (1);
    i = 0;
    pthread_join(data->monitor, NULL);
    while(i < data->philo_nbr)
    {
        pthread_join(data->philos[i].thread_id, NULL);
        i++;
    }
    return (0);
}