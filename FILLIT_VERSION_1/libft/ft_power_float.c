/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 09:12:49 by ibtraore          #+#    #+#             */
/*   Updated: 2016/12/21 09:13:01 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_power_float(double x, int p)
{
	int		i;
	double	nb;

	if (p == 0)
		return (1.0);
	i = 0;
	nb = 1.0;
	if (p > 0)
	{
		while (i < p)
		{
			nb *= x;
			i++;
		}
	}
	else
	{
		while (i > p)
		{
			nb /= x;
			i--;
		}
	}
	return (nb);
}
