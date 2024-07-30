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

void	*monitor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		usleep(200);
		pthread_mutex_lock(&philo->info->dead_mutex);
		if (philo->info->dead || get_time() - philo->last_meal_time > \
				philo->info->time_to_die)
		{
			if (philo->info->dead++ == 0)
				print(philo, "died");
			pthread_mutex_unlock(&philo->info->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->dead_mutex);
		if (philo->info->must_eat > 0 && all_philos_satisfied(philo->info))
		{
			set_dead_and_break(philo);
			break ;
		}
	}
	return (NULL);
}

int	all_philos_satisfied(t_info *info)
{
	int	i;

	pthread_mutex_lock(&info->finish_mutex);
	i = 0;
	while (i < info->philo_num)
	{
		if (info->philos[i].eat_count < info->must_eat)
		{
			pthread_mutex_unlock(&info->finish_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&info->finish_mutex);
	return (1);
}

int	monitor_count(t_philo *philo)
{
	if (philo->info->must_eat > 0 && philo->eat_count >= philo->info->must_eat)
	{
		pthread_mutex_lock(&philo->info->finish_mutex);
		philo->info->finish_count++;
		if (philo->info->finish_count >= philo->info->philo_num)
		{
			philo->info->dead = 1;
			pthread_mutex_unlock(&philo->info->finish_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->info->finish_mutex);
	}
	return (1);
}

int	monitor_finish(t_philo philo)
{
	if (philo.info->finish_count == philo.info->philo_num
		|| philo.info->dead == 1)
		return (1);
	return (0);
}
