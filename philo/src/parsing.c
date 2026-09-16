#include "philo.h"

int check_data(t_data *data)
{
    if (data->time_to_die <= 0)
        return (1);
    if (data->time_to_eat <= 0)
        return (1);
    if (data->time_to_sleep <= 0)
        return (1);
    if (data->meals_counter == 0 || data->meals_counter < -1)
        return (1);
    return (0);
}

void    parse_input(t_data *data, char **argv)
{
    if (is_digit(argv))
        err_exit("Only digits !");
    data->philo_nbr = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
    if (argv[5])
        data->meals_counter = ft_atol(argv[5]);
    else
        data->meals_counter = -1;
    if (check_data(data))
        err_exit("Wrong input");
}