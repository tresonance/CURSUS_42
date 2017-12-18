/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chessboard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:43:11 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/19 15:32:50 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#define INNER_SIZE 4.00

void		append_chessboard(t_obj *chessboard, t_ray ray, t_hit **hit_list)
{
	append_cuboid(chessboard, ray, hit_list);
}

int			square_coordinate(double val)
{
	double	t;

	t = floor(8.0 * (val / (double)INNER_SIZE + 0.5));
	if (t < 0.0)
		return (0);
	else if (t > 7.0)
		return (7);
	else
		return ((int)t);
}

void		set_chessboard_sphere_color(t_obj *chessboard)
{
	t_obj	*obj;

	obj = chessboard;
	if (chessboard)
		obj = chessboard->next;
	while (obj)
	{
		if (!ft_strcmp(obj->name, "\tsphere"))
		{
			obj->matte = scalcol(obj->matte_factor, obj->matte);
			obj->glossy = scalcol(obj->glossy_factor, obj->glossy);
		}
		obj = obj->next;
	}
}

void		chessboard_color(t_obj *chessboard, t_hit *inter)
{
	t_color col[3];
	int		x;
	int		y;

	set_chessboard_sphere_color(chessboard);
	col[0] = (t_color){0.50, 0.30, 0.10};
	col[1] = (t_color){0.30, 0.30, 0.40};
	col[2] = (t_color){0.75, 0.70, 0.10};
	if (inter->point.z < chessboard->c / 2.0 - (double)EPSILON)
		chessboard->matte = col[0];
	else
	{
		if (fabs(inter->point.x) < chessboard->a / 2.0 && fabs(inter->point.y)
				< chessboard->b / 2.0)
		{
			x = square_coordinate(inter->point.x);
			y = square_coordinate(inter->point.y);
			if (0 == ((x + y) & 1))
				chessboard->matte = col[1];
			else
				chessboard->matte = col[2];
		}
		else
			chessboard->matte = col[0];
	}
}
