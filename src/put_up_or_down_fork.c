/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_up_or_down_fork.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:03:20 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/18 23:03:23 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	pick_up_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = (philo->id % philo->info->philo_num);
	if (left < right)
	{
		pthread_mutex_lock(&philo->info->forks[left]);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->forks[right]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->forks[right]);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->info->forks[left]);
	}
	print(philo, "has taken a fork");
}

void	put_down_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = (philo->id % philo->info->philo_num);
	pthread_mutex_unlock(&philo->info->forks[left]);
	pthread_mutex_unlock(&philo->info->forks[right]);
}

bool	is_next_to_eat(t_philo *philo)
{
	unsigned long	min_last_meal_time;
	int				index;
	int				i;

	min_last_meal_time = ULONG_MAX;
	index = -1;
	i = 0;
	while (i < philo->info->philo_num)
	{
		if (philo->info->philos[i].last_meal_time < min_last_meal_time)
		{
			min_last_meal_time = philo->info->philos[i].last_meal_time;
			index = i;
		}
		i++;
	}
	return (philo->id == index + 1);
}
