/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:08:12 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/18 23:08:16 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_dead_and_break(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead_mutex);
	philo->info->dead = 1;
	pthread_mutex_unlock(&philo->info->dead_mutex);
}

int	all_philos_satisfied(t_info *info)
{
	int	i;
	int	all_satisfied;

	i = 0;
	all_satisfied = 1;
	while (i < info->philo_num)
	{
		pthread_mutex_lock(&info->philos[i].eat_count_mutex);
		if (info->philos[i].eat_count < info->must_eat)
			all_satisfied = 0;
		pthread_mutex_unlock(&info->philos[i].eat_count_mutex);
		if (!all_satisfied)
			break ;
		i++;
	}
	return (all_satisfied);
}

int	check_death_and_timeout(t_philo *philo)
{
	unsigned long	last_meal;

	pthread_mutex_lock(&philo->last_meal_time_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	pthread_mutex_lock(&philo->info->dead_mutex);
	if (philo->info->dead)
	{
		pthread_mutex_unlock(&philo->info->dead_mutex);
		return (1);
	}
	if (get_time() - last_meal > philo->info->time_to_die)
	{
		philo->info->dead = 1;
		pthread_mutex_unlock(&philo->info->dead_mutex);
		print(philo, "died");
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead_mutex);
	return (0);
}

int	check_all_satisfied(t_philo *philo)
{
	if (philo->info->must_eat > 0 && all_philos_satisfied(philo->info))
	{
		set_dead_and_break(philo);
		return (1);
	}
	return (0);
}
