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

void	*monitor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		usleep(1000);
		if (check_death_and_timeout(philo))
			break ;
		if (check_all_satisfied(philo))
			break ;
	}
	return (NULL);
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
