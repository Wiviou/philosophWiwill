/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:13:05 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/16 13:13:06 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	clear_data(t_info *info)
{
	int	i;

	i = 0;
	if (info->forks)
	{
		while (i < info->init_count_forks)
		{
			pthread_mutex_destroy_safe(&info->forks[i]);
			pthread_mutex_destroy_safe(&info->philos[i].last_meal_time_mutex);
			if (info->must_eat != -1)
				pthread_mutex_destroy_safe(&info->philos[i].eat_count_mutex);
			i++;
		}
		free(info->forks);
		info->forks = NULL;
	}
	pthread_mutex_destroy_safe(&info->dead_mutex);
	pthread_mutex_destroy_safe(&info->finish_mutex);
	pthread_mutex_destroy_safe(&info->write);
	if (info->philos)
	{
		clearing(info);
	}
}

void	clearing(t_info *info)
{
	if (info->flag == 1)
		free(info->philos);
	info->philos = NULL;
}

void	pthread_mutex_destroy_safe(pthread_mutex_t *mutex)
{
	if (mutex != NULL && pthread_mutex_trylock(mutex) == 0)
	{
		pthread_mutex_unlock(mutex);
		pthread_mutex_destroy(mutex);
	}
}
