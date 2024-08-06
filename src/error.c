/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:50:34 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/02 14:50:39 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	error_check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (check_nb_philo(ft_atol(argv[i])))
		return (ERROR);
	while (++i < argc)
	{
		if (i == 5)
		{
			if (num_check(argv[i]) == ERROR)
				return (ERROR);
		}
		else
			if (num_check(argv[i]) == ERROR || size_check(ft_atol(argv[i])))
				return (ERROR);
		if (ft_atol(argv[i]) == 0)
			return (ERROR);
	}
	return (SUCCESS);
}

void	error_print(int error)
{
	if (error == 42)
	{
		printf("\n🚫 Oops! Something went wrong. 😓\n" \
	"Please check the following: \n\n" \
	"1️⃣  Ensure all arguments are positive numbers within the range:\n" \
	"   Nb of Philo : 1 to 200\n   time_to_die mini 60 (int)\n" \
	"   time_to_eat mini 60 (int)\n   time_to_sleep mini 60 (int)\n" \
	"   nb_of_times_philo_must_eat : 1 to INT_MAX\n" \
	"2️⃣  Make sure none of the arguments are missing. \n" \
	"3️⃣  Verify that the number of arguments is either 4 or 5. \n\n" \
	"-> Exemple of usage : (time has to be in ms Comrade)\n" \
	"-> ./philo number_of_philosophers time_to_die " \
	"time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n" \
	"-> ./philo 4 310 200 100 (Fifth argument isn't obligatory my friend)\n\n");
	}
}

void	handle_error(const char *message, t_info *info)
{
	if (info != NULL)
	{
		clear_data(info);
	}
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	check_pthread_error(int ret, const char *msg)
{
	if (ret != 0)
	{
		printf("%s: %s\n", msg, strerror(ret));
		exit(EXIT_FAILURE);
	}
}
