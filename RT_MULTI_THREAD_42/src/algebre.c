/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebre.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:39:08 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 13:15:57 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		second_degre(double coef[3], double result[])
{
	double a;
	double b;
	double c;
	double delta;

	a = coef[0];
	b = coef[1];
	c = coef[2];
	/*if (fabs(a) <= (double)TOLERANCE)
	{
		if (fabs(b) <= (double)TOLERANCE)
			return (0);
		else
		{
			result[0] = -c / b;
			return (1);
		}
	}*/
	delta = (b * b) - (4 * a * c);
	if (delta < -TOLERANCE)
		return (0);
	if (delta >= -TOLERANCE && delta <= TOLERANCE)
	{
		result[0] = -b / (2.0 * a);
		result[1] = result[0];
		return (1);
	}
	result[0] = (-b + sqrtf(delta)) / (2.0 * a);
	result[1] = (-b - sqrtf(delta)) / (2.0 * a);
	return (2);
}
