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

#include "../includes/rt.h"

#define POS e->cam->pos
#define DIR e->cam->lookat
//#define ROT e->hit_obj->rot

void	rotate_cam_pos(int key, t_env *e)
{
	//if (e->is_obj_selected == 1)
	//	return ;
	if (key == ONE)
		e->cam->pos = (t_vector){POS.x * cosf(e->rot_speed) + POS.y * sinf(-e->rot_speed),
			POS.x * sinf(e->rot_speed) + POS.y * cosf(e->rot_speed), POS.z};
	if (key == TWO)
		e->cam->pos = (t_vector){POS.x * cosf(e->rot_speed) + POS.y * sinf(e->rot_speed),
			POS.x * sinf(-e->rot_speed) + POS.y * cosf(e->rot_speed), POS.z};
	if (key == FOUR)
		e->cam->pos = (t_vector){POS.x * cosf(e->rot_speed) + POS.z * sinf(e->rot_speed), POS.y,
			POS.x * sinf(-e->rot_speed) + POS.z * cosf(e->rot_speed)};
	if (key == FIVE)
		e->cam->pos = (t_vector){POS.x * cosf(e->rot_speed) + POS.z * sinf(-e->rot_speed),
			POS.y, POS.x * sinf(e->rot_speed) + POS.z * cosf(e->rot_speed)};
	if (key == SEVEN)
		e->cam->pos = (t_vector){POS.x, POS.y * cosf(e->rot_speed) + POS.z *
			sinf(-e->rot_speed), POS.y * sinf(e->rot_speed) + POS.z * cosf(e->rot_speed)};
	if (key == HEIGHT)
		e->cam->pos = (t_vector){POS.x, POS.y * cosf(e->rot_speed) + POS.z * sinf(e->rot_speed),
			POS.y * sinf(-e->rot_speed) + POS.z * cosf(e->rot_speed)};
}

void	rotate_cam_lookat(int key, t_env *e)
{
	//if (e->is_obj_selected == 1)
	//	return ;
	if (key == ONE)
		e->cam->lookat = (t_vector){DIR.x * cosf(e->rot_speed) + DIR.y * sinf(-e->rot_speed),
			DIR.x * sinf(e->rot_speed) + DIR.y * cosf(e->rot_speed), DIR.z};
	if (key == TWO)
		e->cam->lookat = (t_vector){DIR.x * cosf(e->rot_speed) + DIR.y * sinf(e->rot_speed),
			DIR.x * sinf(-e->rot_speed) + DIR.y * cosf(e->rot_speed), DIR.z};
	if (key == FOUR)
		e->cam->lookat = (t_vector){DIR.x * cosf(e->rot_speed) + DIR.z * sinf(e->rot_speed),
			DIR.y, DIR.x * sinf(-e->rot_speed) + DIR.z * cosf(e->rot_speed)};
	if (key == FIVE)
		e->cam->lookat = (t_vector){DIR.x * cosf(e->rot_speed) + DIR.z * sinf(-e->rot_speed),
			DIR.y, DIR.x * sinf(e->rot_speed) + DIR.z * cosf(e->rot_speed)};
	if (key == SEVEN)
		e->cam->lookat = (t_vector){DIR.x, DIR.y * cosf(e->rot_speed) + DIR.z *
			sinf(-e->rot_speed), DIR.y * sinf(e->rot_speed) + DIR.z * cosf(e->rot_speed)};
	if (key == HEIGHT)
		e->cam->lookat = (t_vector){DIR.x, DIR.y * cosf(e->rot_speed) + DIR.z * sinf(e->rot_speed),
			DIR.y * sinf(-e->rot_speed) + DIR.z * cosf(e->rot_speed)};
}

/*void	rotate_selected_obj_rot(int key, t_env *e)
{
	if (e->is_obj_selected == 1)
	{
		if (key == ONE)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(e->rot_speed) + ROT.y *
				sinf(-e->rot_speed), ROT.x * sinf(e->rot_speed) + ROT.y * cosf(e->rot_speed),
					ROT.z, 0.0};
		if (key == TWO)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(e->rot_speed) + ROT.y * sinf(e->rot_speed)
				, ROT.x * sinf(-e->rot_speed) + ROT.y * cosf(e->rot_speed), ROT.z, 0.0};
		if (key == FOUR)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(e->rot_speed) + ROT.z * sinf(e->rot_speed)
				, ROT.y, ROT.x * sinf(-e->rot_speed) + ROT.z * cosf(e->rot_speed), 0.0};
		if (key == FIVE)
			e->hit_obj->rot = (t_vector){ROT.x * cosf(e->rot_speed) + ROT.z *
				sinf(-e->rot_speed), ROT.y, ROT.x * sinf(e->rot_speed) + ROT.z * cosf(e->rot_speed),
					0.0};
		if (key == SEVEN)
			e->hit_obj->rot = (t_vector){ROT.x, ROT.y * cosf(e->rot_speed) + ROT.z *
				sinf(-e->rot_speed), ROT.y * sinf(e->rot_speed) + ROT.z * cosf(e->rot_speed), 0.0};
		if (key == HEIGHT)
			e->hit_obj->rot = (t_vector){ROT.x, ROT.y * cosf(e->rot_speed) + ROT.z *
				sinf(e->rot_speed), ROT.y * sinf(-e->rot_speed) + ROT.z * cosf(e->rot_speed), 0.0};
	}
}*/

void	rotate_camera(int key, t_env *e)
{
	rotate_cam_pos(key, e);
	rotate_cam_lookat(key, e);
	//rotate_selected_obj_rot(key, e);
}
