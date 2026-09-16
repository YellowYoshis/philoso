#include "philo.h"

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
