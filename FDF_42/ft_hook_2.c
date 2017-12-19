/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 09:12:12 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/25 23:56:46 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		wait_rotate_z_event(int key, t_env *e)
{
	if (key == ROT_Z_P)
	{
		e->m = ft_rotate_z(M_PI / 48);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
	else if (key == ROT_Z_N)
	{
		e->m = ft_rotate_z(-M_PI / 48);
		all_points(e, e->m);
		free(e->m);
		e->m = NULL;
	}
}

void		wait_others_event(int key, t_env *e)
{
	if (key == ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(1);
	}
}

int			key_hook(int key, t_env *e)
{
	wait_translate_left_right_event(key, e);
	wait_translate_up_down_event(key, e);
	wait_zoom_event(key, e);
	wait_rotate_x_event(key, e);
	wait_rotate_y_event(key, e);
	wait_rotate_z_event(key, e);
	wait_others_event(key, e);
	set_image(e);
	return (0);
}
