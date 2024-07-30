/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:51:05 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/02 14:51:06 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	case_one_philo(t_info info)
{
	print(&info.philos[0], "has taken a fork");
	usleep(info.time_to_die * 1000);
	print(&info.philos[0], "died");
}

int	main(int argc, char **argv)
{
	t_info	info;

	if ((argc < 5 || argc > 6 || \
		error_check(argc, argv) == ERROR))
	{
		error_print(42);
		return (1);
	}
	start_simulation(argc, argv, &info);
	clear_data(&info);
	return (0);
}

void	start_simulation(int argc, char **argv, t_info *info)
{
	if (set_param(info, argc, argv) == ERROR)
	{
		printf("Error param setting\n");
		return ;
	}
	if (initialize_philos(info) == ERROR)
	{
		handle_error("Failed to initialize philosophers\n", info);
		return ;
	}
	info->philos = set_philosopher(info->philo_num, *info);
	if (info->philos == NULL)
	{
		printf ("Fail initializing philos stats\n");
		return ;
	}
	if (info->philo_num == 1)
		case_one_philo(*info);
	else
		exec_philosophers(*info);
}
