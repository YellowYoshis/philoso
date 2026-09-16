#include "philo.h"

int is_digit(char **argv)
{
    int i;
    int j;

    i = 1;
    while(argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (1);
            j++;
        }
        i++;
    }
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
    pthread_mutex_destroy(&data->printer);
    pthread_mutex_destroy(&data->is_stopped);
}

void    err_exit(char *error)
{
    printf("%s\n", error);
    exit(EXIT_FAILURE);
}

void    ft_cleanup(t_data *data)
{
    free(data->philos);
    free(data->forks);
}