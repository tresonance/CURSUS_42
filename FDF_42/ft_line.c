/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 09:33:08 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 23:38:21 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		slope_of_current_line(t_env *e, t_point *point1, t_point *point2)
{
	e->dx = fabs(point1->x - point2->x);
	e->flagdx = point1->x < point2->x ? 1 : -1;
	e->dy = fabs(point1->y - point2->y);
	e->flagdy = point1->y < point2->y ? 1 : -1;
	e->flag = (e->dx > e->dy ? e->dx : -e->dy) * 0.5;
}

void		set_pixel(t_point *p, int color, t_env *e)
{
	int index;

	if ((int)p->x >= 0 && (int)p->x < WIDTH && (int)p->y >= 0
			&& (int)p->y < HEIGHT)
	{
		index = ((int)p->y * e->size_line) + ((int)p->x * e->bpp / 8);
		e->pixel[index] = color;
		e->pixel[++index] = color >> 8;
		e->pixel[++index] = color >> 16;
		e->pixel[++index] = color >> 24;
	}
}

int			valid_point(t_point *point1)
{
	if (!(point1->x > WIDTH + 100 || point1->x <= 0 ||
				point1->y > HEIGHT + 100 || point1->y <= 0))
		return (1);
	else
		return (0);
}

void		line_loop(t_env *e, t_point p0, t_point p1)
{
	double	val;
	int		booll;

	booll = 1;
	while (booll == 1 && !((int)p0.x == (int)p1.x && (int)p0.y == (int)p1.y))
	{
		if (valid_point(&p0) == 1)
			set_pixel(&p0, ft_color_palette(p0, p0), e);
		val = e->flag;
		booll = 0;
		if (val > -e->dx && (int)p0.x != (int)p1.x)
		{
			e->flag -= e->dy;
			p0.x += e->flagdx;
			booll = 1;
		}
		if (val < e->dy && (int)p0.y != (int)p1.y)
		{
			e->flag += e->dx;
			p0.y += e->flagdy;
			booll = 1;
		}
	}
}

void		line(t_env *e, t_point p0, t_point p1)
{
	if (!valid_point(&p0) && !valid_point(&p1))
		return ;
	slope_of_current_line(e, &p0, &p1);
	line_loop(e, p0, p1);
}
