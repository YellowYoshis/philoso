/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:32:58 by jturrel           #+#    #+#             */
/*   Updated: 2026/09/18 15:52:10 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_meals_eaten(t_data *data)
{
	int	done;

	pthread_mutex_lock(&data->meals_eaten_mutex);
	done = (data->meal_eaten == data->philo_nbr);
	pthread_mutex_unlock(&data->meals_eaten_mutex);
	return (done);
}

int	print_action(t_philo *philo, char *msg)
{
	if (simulation_stopped(philo->data))
	{
		return (1);
	}
	pthread_mutex_lock(&philo->data->printer);
	if (simulation_stopped(philo->data))
	{
		pthread_mutex_unlock(&philo->data->printer);
		return (1);
	}
	printf("%ld %d %s\n", get_time_ms() - philo->data->start_time, philo->id,
		msg);
	pthread_mutex_unlock(&philo->data->printer);
	return (0);
}

void	print_death(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->printer);
	stop_simulation(philo->data);
	printf("%ld %d %s\n", get_time_ms() - philo->data->start_time, philo->id,
		msg);
	pthread_mutex_unlock(&philo->data->printer);
}

void	destroy_mutex(t_data *data)
{
	int		i;
	long	len;

	i = 0;
	len = data->philo_nbr;
	while (i < len)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meals);
		i++;
	}
	pthread_mutex_destroy(&data->meals_eaten_mutex);
	pthread_mutex_destroy(&data->printer);
	pthread_mutex_destroy(&data->is_stopped);
}
