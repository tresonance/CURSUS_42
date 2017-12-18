/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:45:24 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/19 13:00:55 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_color		addcol(t_color a, t_color c)
{
	return ((t_color){a.r + c.r, a.g + c.g, a.b + c.b});
}

t_color		scalcol(double a, t_color c)
{
	return ((t_color){a * c.r, a * c.g, a * c.b});
}

t_color		mulcol(t_color a, t_color c)
{
	return ((t_color){a.r * c.r, a.g * c.g, a.b * c.b});
}

t_color		averagecol(t_color col, int num)
{
	t_color average;

	average.r = col.r / (double)num;
	average.g = col.g / (double)num;
	average.b = col.b / (double)num;
	return (average);
}

t_color		barycentre_color(t_color c1, t_color c2, t_color c3,
		double *pondere)
{
	t_color color;
	t_color col1;
	t_color col2;
	t_color col3;

	col1 = scalcol(pondere[0], c1);
	col2 = scalcol(pondere[1], c2);
	col3 = scalcol(pondere[2], c3);
	col1 = addcol(col1, col2);
	color = addcol(col1, col3);
	return (color);
}
