/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:11:59 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/16 13:12:05 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->info->write);
	pthread_mutex_lock(&philo->info->dead_mutex);
	if (!philo->info->dead || !philo->info->too_bad_no_death)
	{
		if (philo->info->dead == 1)
			philo->info->too_bad_no_death = 1;
		printf("%lu %d %s\n", get_time(), philo->id, action);
	}
	pthread_mutex_unlock(&philo->info->dead_mutex);
	pthread_mutex_unlock(&philo->info->write);
}
