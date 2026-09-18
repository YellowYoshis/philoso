/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:31:38 by jturrel           #+#    #+#             */
/*   Updated: 2026/09/18 15:52:42 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->forks = ft_calloc(data->philo_nbr + 1, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (1);
	while (i < data->philo_nbr)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].meals, NULL);
		i++;
	}
	return (0);
}

void	give_fork(t_data *data)
{
	int		i;
	long	len;

	len = data->philo_nbr;
	i = 0;
	while (i < len)
	{
		data->philos[i].right_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].left_fork = &data->forks[len - 1];
		else
			data->philos[i].left_fork = &data->forks[i - 1];
		i++;
	}
}

int	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->philos = ft_calloc(data->philo_nbr + 1, sizeof(t_philo));
	if (!data->philos)
		return (1);
	while (i < data->philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meal_counter = data->meals_counter;
		i++;
	}
	if (init_fork(data))
		return (1);
	pthread_mutex_init(&data->meals_eaten_mutex, NULL);
	pthread_mutex_init(&data->printer, NULL);
	pthread_mutex_init(&data->is_stopped, NULL);
	give_fork(data);
	return (0);
}
