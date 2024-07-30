/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:50:47 by wkeiser           #+#    #+#             */
/*   Updated: 2024/07/02 14:50:50 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_space(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
	{
		return (1);
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	ret;
	int		sign;

	i = 0;
	ret = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!(str[i] >= 48 && str[i] <= 57))
		return (0);
	while (str[i] >= 48 && str[i] <= 57)
	{
		ret += (str[i] - 48);
		if (str[i + 1] >= 48 && str[i + 1] <= 57)
			ret *= 10;
		i++;
	}
	return (ret * sign);
}
