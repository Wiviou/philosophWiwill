/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:51:13 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/02 14:51:16 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	initialize_philos(t_info *info)
{
	int	i;

	info->flag = 1;
	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			info->init_count_forks = i;
			info->flag = 0;
			return (ERROR);
		}
		i++;
	}
	info->init_count_forks = info->philo_num;
	return (SUCCESS);
}

t_philo	*set_philosopher(int num, t_info info)
{
	t_philo			*philo;
	pthread_mutex_t	dead;
	int				i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * num);
	if (philo == NULL)
		return (NULL);
	if (pthread_mutex_init(&dead, NULL) != 0)
	{
		free(philo);
		return (NULL);
	}
	while (i < num)
	{
		set_philosopher_param(&philo[i], &info, i);
		i++;
	}
	philo->dead_mutex = dead;
	return (philo);
}

void	exec_philosophers(t_info info)
{
	pthread_t	*th;
	int			i;

	th = malloc(sizeof(pthread_t) * info.philo_num);
	if (th == NULL)
	{
		write(2, "Error: Failed to allocate memory for threads\n", 46);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < info.philo_num)
	{
		usleep(10);
		if (pthread_create(&th[i], NULL, &work, &info.philos[i]) != 0)
		{
			write(2, "Error: Failed to create a thread\n", 33);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = -1;
	while (++i < info.philo_num)
		pthread_join(th[i], NULL);
	free(th);
}
