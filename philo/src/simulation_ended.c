/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_ended.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:32:05 by jturrel           #+#    #+#             */
/*   Updated: 2026/09/18 15:51:38 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_last_meal(t_data *data, long last_meal, int i)
{
	pthread_mutex_lock(&data->philos[i].meals);
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->philos[i].meals);
	if (get_time_ms() - last_meal > data->time_to_die)
	{
		print_death(&data->philos[i], "died");
		return (1);
	}
	return (0);
}
