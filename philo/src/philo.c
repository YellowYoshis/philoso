#include "philo.h"

void    print_struct(t_data *data)
{
    printf("philo numbers: %ld\n", data->philo_nbr);
    printf("time to die: %ld\n", data->time_to_die);
    printf("time to eat: %ld\n", data->time_to_eat);
    printf("time to sleep: %ld\n", data->time_to_sleep);
    printf("meals_counter: %ld\n", data->meals_counter);
}

int main(int argc, char **argv)
{
    t_data  data;
    if (argc != 5 && argc != 6 )
        return (1);
    parse_input(&data, argv);
    print_struct(&data);
    if(data_init(&data))
    {
        ft_cleanup(&data);
        return (1);
    }
    simulation_started(&data);
    destroy_mutex(&data);
    ft_cleanup(&data);
    return (0);
}