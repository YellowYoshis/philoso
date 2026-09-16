#include "philo.h"

void *simulation(void *arg)
{
    t_philo     *philo;
    long    now;

    philo = (t_philo *)arg;
    printf("data->philo_nbr %ld\n", philo->data->philo_nbr);
    now = get_time_ms();
    while (1)
    {
        if(now >= philo->data->start_time + 2000)
            break ;
        now = get_time_ms();
    }
    while(!simulation_stopped(philo->data))
    {
        is_eating(philo);
        is_sleeping(philo);
        is_thinking(philo);
    }
    return (NULL);
}

void    *simulation_monitor(void *arg)
{
    t_philo     *philo;
    int     i;

    i = 0;
    philo = (t_philo *)arg;
    printf("data->philo_nbr %ld\n", philo->data->philo_nbr);
    while (1)
    {
        i = 0;
        while (i < philo->data->philo_nbr)
        {
            if (philo->data->philos[i].last_meal_time - get_time_ms() > philo->data->time_to_die)
            {
                print_action(&philo->data->philos[i], "is dead");
                stop_simulation(philo->data);    
            }
            i++;
        }
    }
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
    if (pthread_create(&data->monitor, NULL, simulation_monitor, &data->philos[i]))
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