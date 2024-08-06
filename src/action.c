/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:50:27 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/02 14:50:57 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*work(void *philo_ptr)
{
	t_philo		*philo;
	pthread_t	monitor_thread;
	int			is_dead;

	philo = (t_philo *)philo_ptr;
	philo->last_meal_time = get_time();
	pthread_create(&monitor_thread, NULL, &monitor, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->info->dead_mutex);
		is_dead = philo->info->dead;
		pthread_mutex_unlock(&philo->info->dead_mutex);
		if (is_dead)
			break ;
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	pthread_join(monitor_thread, NULL);
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (philo->eat_count < philo->info->must_eat || philo->info->must_eat == -1)
	{
		pick_up_forks(philo);
		print(philo, "is eating");
		pthread_mutex_lock(&philo->last_meal_time_mutex);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->last_meal_time_mutex);
		usleep(philo->info->time_to_eat * 1000);
		put_down_forks(philo);
		pthread_mutex_lock(&philo->eat_count_mutex);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->eat_count_mutex);
	}
	else
	{
		philo->dont_eat++;
		return ;
	}
}

void	sleep_philo(t_philo *philo)
{
	if (!philo->dont_eat)
	{
		print(philo, "is sleeping");
		usleep(philo->info->time_to_sleep * 1000);
	}
}

void	think(t_philo *philo)
{
	print(philo, "is thinking");
	if (!philo->dont_eat)
		usleep(1000);
	else
		usleep(philo->info->time_to_sleep * 1000);
}
