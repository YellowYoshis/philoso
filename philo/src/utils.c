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

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void    ft_cleanup(t_data *data)
{
    free(data->philos);
    free(data->forks);
}