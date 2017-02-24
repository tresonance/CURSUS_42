/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:06:22 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:06:33 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_deci(char *str, double i)
{
	int deci;

	deci = -1;
	str++;
	while (*str >= '0' && *str <= '9' && *str)
		i = i + ((*str++ - '0') * ft_power_float(10, deci--));
	return (i);
}

double			ft_atof(char *str)
{
	double		i;

	i = 0;
	while ((*str >= 0 && *str <= 26) || (*str >= 28 && *str <= 32))
		str++;
	if (*str == '-')
	{
		str++;
		while (*str >= '0' && *str <= '9' && *str)
			i = (i * 10) + *str++ - '0';
		if (*str == '.')
			i = ft_deci(str, i);
		return (-i);
	}
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9' && *str)
		i = (i * 10) + *str++ - '0';
	if (*str == '.')
		i = ft_deci(str, i);
	return (i);
}
