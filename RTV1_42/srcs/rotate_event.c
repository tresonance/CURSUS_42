/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 05:46:12 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/11 02:28:22 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

#define POS e->cam->pos
#define DIR e->cam->dir
#define ROT e->hit_obj->rot

void	rotate_cam_pos(int key, t_env *e)
{
	if (e->is_obj_selected == 1)
		return ;
	if (key == ONE)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.y * sinf(-0.13),
			POS.x * sinf(0.13) + POS.y * cosf(0.13), POS.z, 1.0};
	if (key == TWO)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.y * sinf(0.13),
			POS.x * sinf(-0.13) + POS.y * cosf(0.13), POS.z, 1.0};
	if (key == FOUR)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.z * sinf(0.13), POS.y,
			POS.x * sinf(-0.13) + POS.z * cosf(0.13), 1.0};
	if (key == FIVE)
		e->cam->pos = (t_vector){POS.x * cosf(0.13) + POS.z * sinf(-0.13),
			POS.y, POS.x * sinf(0.13) + POS.z * cosf(0.13), 1.0};
	if (key == SEVEN)
		e->cam->pos = (t_vector){POS.x, POS.y * cosf(0.13) + POS.z *
			sinf(-0.13), POS.y * sinf(0.13) + POS.z * cosf(0.13), 1.0};
	if (key == HEIGHT)
		e->cam->pos = (t_vector){POS.x, POS.y * cosf(0.13) + POS.z * sinf(0.13),
			POS.y * sinf(-0.13) + POS.z * cosf(0.13), 1.0};
}

void	rotate_cam_dir(int key, t_env *e)
{
	if (e->is_obj_selected == 1)
		return ;
	if (key == ONE)
		e->cam->dir = (t_vector){DIR.x * cosf(0.13) + DIR.y * sinf(-0.13),
			DIR.x * sinf(0.13) + DIR.y * cosf(0.13), DIR.z, 1.0};
	if (key == TWO)
		e->cam->dir = (t_vector){DIR.x * cosf(0.13) + DIR.y * sinf(0.13),
			DIR.x * sinf(-0.13) + DIR.y * cosf(0.13), DIR.z, 1.0};
	if (key == FOUR)
		e->cam->dir = (t_vector){DIR.x * cosf(0.13) + DIR.z * sinf(0.13),
			DIR.y, DIR.x * sinf(-0.13) + DIR.z * cosf(0.13), 1.0};
	if (key == FIVE)
		e->cam->dir = (t_vector){DIR.x * cosf(0.13) + DIR.z * sinf(-0.13),
			DIR.y, DIR.x * sinf(0.13) + DIR.z * cosf(0.13), 1.0};
	if (key == SEVEN)
		e->cam->dir = (t_vector){DIR.x, DIR.y * cosf(0.13) + DIR.z *
			sinf(-0.13), DIR.y * sinf(0.13) + DIR.z * cosf(0.13), 1.0};
	if (key == HEIGHT)
		e->cam->dir = (t_vector){DIR.x, DIR.y * cosf(0.13) + DIR.z * sinf(0.13),
			DIR.y * sinf(-0.13) + DIR.z * cosf(0.13), 1.0};
}

void	rotate_selected_obj_rot(int key, t_env *e)
{
	if (e->is_obj_selected == 1)
	{
		if (key == ONE)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(0.13) + ROT.y *
				sinf(-0.13), ROT.x * sinf(0.13) + ROT.y * cosf(0.13),
					ROT.z, 0.0};
		if (key == TWO)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(0.13) + ROT.y * sinf(0.13)
				, ROT.x * sinf(-0.13) + ROT.y * cosf(0.13), ROT.z, 0.0};
		if (key == FOUR)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(0.13) + ROT.z * sinf(0.13)
				, ROT.y, ROT.x * sinf(-0.13) + ROT.z * cosf(0.13), 0.0};
		if (key == FIVE)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(0.13) + ROT.z *
				sinf(-0.13), ROT.y, ROT.x * sinf(0.13) + ROT.z * cosf(0.13),
					0.0};
		if (key == SEVEN)
			e->hit_obj->rot = (t_vector){ROT.x, ROT.y * cosf(0.13) + ROT.z *
				sinf(-0.13), ROT.y * sinf(0.13) + ROT.z * cosf(0.13), 0.0};
		if (key == HEIGHT)
			e->hit_obj->rot = (t_vector){ROT.x, ROT.y * cosf(0.13) + ROT.z *
				sinf(0.13), ROT.y * sinf(-0.13) + ROT.z * cosf(0.13), 0.0};
	}
}

void	rotate_camera(int key, t_env *e)
{
	rotate_cam_pos(key, e);
	rotate_cam_dir(key, e);
	rotate_selected_obj_rot(key, e);
}
