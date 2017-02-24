/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 09:11:50 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 09:31:14 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		wait_translate_left_right_event(int key, t_env *e)
{
	if (key == RIGHT)
	{
		e->xstart = 10;
		e->m = ft_translate(e->xstart, 0, 0);
		all_points(e, e->m);
		free(e->m);
	}
	else if (key == LEFT)
	{
		e->xstart = -10;
		e->m = ft_translate(e->xstart, 0, 0);
		all_points(e, e->m);
		free(e->m);
	}
}

void		wait_translate_up_down_event(int key, t_env *e)
{
	if (key == UP)
	{
		e->ystart = 10;
		e->m = ft_translate(0, e->ystart, 0);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
	else if (key == DOWN)
	{
		e->ystart = -10;
		e->m = ft_translate(0, e->ystart, 0);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
}

void		wait_zoom_event(int key, t_env *e)
{
	if (key == ZOOM_UP && e->zoom < 100)
	{
		e->zoom = 1.1;
		e->m = ft_scale(e->zoom, e->zoom, 1);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
	else if (key == ZOOM_DOWN && e->zoom > 0)
	{
		e->zoom = 1 / 1.1;
		e->m = ft_scale(e->zoom, e->zoom, 1);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
}

void		wait_rotate_x_event(int key, t_env *e)
{
	if (key == ROT_X_P)
	{
		e->m = ft_rotate_x(M_PI / 48);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
	else if (key == ROT_X_N)
	{
		e->m = ft_rotate_x(-M_PI / 48);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
}

void		wait_rotate_y_event(int key, t_env *e)
{
	if (key == ROT_Y_P)
	{
		e->m = ft_rotate_y(M_PI / 48);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
	else if (key == ROT_Y_N)
	{
		e->m = ft_rotate_y(-M_PI / 48);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
}
