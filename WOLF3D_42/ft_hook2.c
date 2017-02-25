/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 03:43:55 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/25 06:29:07 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		close_window(t_env *e)
{
	(void)e->mlx;
	exit(EXIT_SUCCESS);
	return (0);
}

int			wait_key_event(int key, t_env *e)
{
	if (e->frame_num == 1)
	{
		wait_rot_event(key, e);
		wait_translate_event(key, e);
		increase_decrease_movement_speed(key, e);
		if (key == ESC)
			close_window(e);
		key == R ? init_env(e) : 0;
		load_untextured_img(e);
	}
	return (0);
}

int			wait_key_event2(int key, t_env *e)
{
	if (e->frame_num == 2)
	{
		wait_rot_event(key, e);
		wait_translate_event2(key, e);
		increase_decrease_movement_speed(key, e);
		play_music(key);
		if (key == ESC)
			close_window(e);
		if (key == R)
			init_env2(e);
		load_textured_img(e);
	}
	return (0);
}

int			wait_key_event3(int key, t_env *e)
{
	if (e->frame_num == 3)
	{
		wait_rot_event(key, e);
		wait_translate_event3(key, e);
		increase_decrease_movement_speed(key, e);
		play_music(key);
		if (key == ESC)
			close_window(e);
		if (key == R)
			init_env3(e);
		load_textured_sprite_img(e);
	}
	return (0);
}
