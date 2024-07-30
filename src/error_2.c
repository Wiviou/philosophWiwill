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

int	range_nb_check(long nb)
{
	if (nb < 1 || nb > INT_MAX)
		return (ERROR);
	return (SUCCESS);
}

int	size_check(long nb)
{
	if (nb < 60 || nb > INT_MAX)
		return (ERROR);
	return (SUCCESS);
}

int	num_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (ERROR);
	if (str[i] == '+')
		i++;
	if (str[i] == '0')
		return (ERROR);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (ERROR);
		}
		i++;
	}
	if (range_nb_check(ft_atol(str)))
		return (ERROR);
	return (SUCCESS);
}

int	check_nb_philo(long nb)
{
	if (nb < 1 || nb > 200)
		return (ERROR);
	return (SUCCESS);
}
