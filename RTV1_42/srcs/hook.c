/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 07:51:24 by ibtraore          #+#    #+#             */
/*   Updated: 2017/12/09 16:08:50 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int				close_hook_func(int key, t_env *e)
{
	(void)key;
	clear_env(&e);
	return (0);
}

int				expose_hook_func(t_env *e)
{
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->mlx.img, 0, 0);
	return (0);
}

int				mouse_hook_func(int button, int x, int y, t_env *e)
{
	if (button == 1 && x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if (1 == clicked_obj_info(x, y, e))
		{
			if (e->is_obj_selected == 1)
				draw_obj(e);
		}
		else
		{
			free(e->hit_obj);
			e->hit_obj = NULL;
			e->is_obj_selected = 0;
		}
	}
	return (0);
}

int				key_hook_func(int key, t_env *e)
{
	if (key == ESCAPE)
		clear_env(&e);
	if (key == V)
		e->aa *= 2;
	if (key == C)
		e->aa /= 2;
	e->aa = (e->aa < 1) ? 1 : e->aa;
	if (key == B)
		e->aa = 1;
	printf("[key : %d ]\n", key);
	translate(key, e);
	rotate_camera(key, e);
	draw_obj(e);
	return (0);
}
