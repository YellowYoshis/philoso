/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:31:45 by jturrel           #+#    #+#             */
/*   Updated: 2026/09/18 15:31:46 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solo_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	while (!simulation_stopped(philo->data))
		;
	pthread_mutex_unlock(philo->right_fork);
}

int	philo_is_pair(t_philo *philo)
{
	if (simulation_stopped(philo->data))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	if (print_action(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	if (print_action(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	philo_is_unpair(t_philo *philo)
{
	if (simulation_stopped(philo->data))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	if (print_action(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	if (print_action(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	fork_management(t_philo *philo)
{
	if (philo->data->philo_nbr == 1)
	{
		solo_philo(philo);
		return (1);
	}
	if (philo->id % 2 == 0)
	{
		if (philo_is_pair(philo))
			return (1);
	}
	else
	{
		if (philo_is_unpair(philo))
			return (1);
	}
	return (0);
}
