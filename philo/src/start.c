/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:32:23 by jturrel           #+#    #+#             */
/*   Updated: 2026/09/18 15:52:24 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_counter(t_philo *philo)
{
	if (philo->meal_counter > 0)
	{
		pthread_mutex_lock(&philo->meals);
		philo->meal_counter--;
		pthread_mutex_unlock(&philo->meals);
	}
	if (philo->meal_counter == 0)
	{
		pthread_mutex_lock(&philo->data->meals_eaten_mutex);
		philo->data->meal_eaten++;
		pthread_mutex_unlock(&philo->data->meals_eaten_mutex);
		pthread_mutex_lock(&philo->meals);
		philo->full = 1;
		pthread_mutex_unlock(&philo->meals);
		return (1);
	}
	return (0);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time_ms() < philo->data->start_time)
		;
	if (philo->data->philo_nbr % 2 == 0 && philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (!simulation_stopped(philo->data))
	{
		if (is_eating(philo))
			return (NULL);
		if (meal_counter(philo))
			return (NULL);
		if (is_sleeping(philo))
			return (NULL);
		if (is_thinking(philo))
			return (NULL);
	}
	return (NULL);
}

int	philo_is_full(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].meals);
	if (data->philos[i].full == 1)
	{
		pthread_mutex_unlock(&data->philos[i].meals);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->philos[i].meals);
		return (0);
	}
}

void	*simulation_monitor(void *arg)
{
	t_data	*data;
	int		i;
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
			if (all_meals_eaten(data))
				return (NULL);
			if (!philo_is_full(data, i))
			{
				if (check_last_meal(data, last_meal, i))
					return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	simulation_started(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_ms() + 800;
	while (i < data->philo_nbr)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread_id, NULL, simulation,
				&data->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, simulation_monitor, data))
		return (1);
	i = 0;
	pthread_join(data->monitor, NULL);
	while (i < data->philo_nbr)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}
