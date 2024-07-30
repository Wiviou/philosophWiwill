/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:51:30 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/02 14:51:32 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_basic(t_info *info, char **argv)
{
	info->dead = 0;
	info->too_bad_no_death = 0;
	info->philo_num = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	info->must_eat = -1;
	info->finish_count = 0;
	info->flag = 0;
}

int	pthread_wfd_init(t_info *info)
{
	if (pthread_mutex_init(&info->write, NULL) != 0)
	{
		return (ERROR);
	}
	if (pthread_mutex_init(&info->finish_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&info->write);
		return (ERROR);
	}
	if (pthread_mutex_init(&info->dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&info->write);
		pthread_mutex_destroy(&info->finish_mutex);
		return (ERROR);
	}
	return (SUCCESS);
}

int	init_fork_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&info->forks[--i]);
			free(info->forks);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	set_param(t_info *info, int argc, char **argv)
{
	set_basic(info, argv);
	if (argc == 6)
		info->must_eat = ft_atol(argv[5]);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (info->forks == NULL)
		return (ERROR);
	if (init_fork_mutexes(info) != SUCCESS)
		return (ERROR);
	if (pthread_wfd_init(info) != SUCCESS)
	{
		free(info->forks);
		return (ERROR);
	}
	return (SUCCESS);
}

void	set_philosopher_param(t_philo *philo, t_info *info, int i)
{
	philo->info = info;
	philo->eat_count = 0;
	philo->last_meal_time = get_time();
	philo->dont_eat = 0;
	philo->id = i + 1;
	philo->priority = 0;
	info->flag = 1;
}
