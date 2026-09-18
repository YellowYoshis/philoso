#include "philo.h"

int main(int argc, char **argv)
{
    t_data  data;
    if (argc != 5 && argc != 6 )
        return (1);
    if(parse_input(&data, argv))
        return (1);
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