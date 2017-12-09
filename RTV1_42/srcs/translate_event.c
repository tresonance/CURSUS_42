/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 01:21:04 by ibtraore          #+#    #+#             */
/*   Updated: 2017/12/09 16:16:33 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

static void		repere(t_env *e, t_vector *n, t_vector *r)
{
	*n = subvect(&e->cam->pos, &e->cam->dir);
	normalize(&(*n));
	*r = crossvect(n, &(t_vector){0.0, 1.0, 0.0, 0.0});
	normalize(&(*r));
	e->up = crossvect(&(*r), &(*n));
	normalize(&e->up);
}

void			translate_cam_pos(int key, t_vector r, t_vector n, t_env *e)
{
	t_vector	pos;

	pos = e->cam->pos;
	if (key == RIGHT)
		e->cam->pos = (t_vector){pos.x + r.x * 10.0, pos.y + r.y * 10.0,
			pos.z + r.z * 10.0, 1.0};
	else if (key == LEFT)
		e->cam->pos = (t_vector){pos.x - r.x * 10.0, pos.y - r.y * 10.0,
			pos.z - r.z * 10.0, 1.0};
	else if (key == UP)
		e->cam->pos = (t_vector){pos.x + e->up.x * 10.0, pos.y + e->up.y * 10.0,
			pos.z + e->up.z * 10.0, 1.0};
	else if (key == DOWN)
		e->cam->pos = (t_vector){pos.x - e->up.x * 10.0, pos.y - e->up.y * 10.0,
			pos.z - e->up.z * 10.0, 1.0};
	else if (key == PLUS)
		e->cam->pos = (t_vector){pos.x + n.x * 10.0, pos.y + n.y * 10.0, pos.z +
			n.z * 10.0, 1.0};
	else if (key == MINUS)
		e->cam->pos = (t_vector){pos.x - n.x * 10.0, pos.y - n.y * 10.0, pos.z -
			n.z * 10.0, 1.0};
}

void			translate_cam_dir(int key, t_vector r, t_vector n, t_env *e)
{
	t_vector	dir;

	dir = e->cam->dir;
	if (key == RIGHT)
		e->cam->dir = (t_vector){dir.x + r.x * 10.0, dir.y + r.y * 10.0,
			dir.z + r.z * 10.0, 1.0};
	else if (key == LEFT)
		e->cam->dir = (t_vector){dir.x - r.x * 10.0, dir.y - r.y * 10.0,
			dir.z - r.z * 10.0, 1.0};
	else if (key == UP)
		e->cam->dir = (t_vector){dir.x + e->up.x * 10.0, dir.y + e->up.y * 10.0,
			dir.z + e->up.z * 10.0, 1.0};
	else if (key == DOWN)
		e->cam->dir = (t_vector){dir.x - e->up.x * 10.0, dir.y - e->up.y * 10.0,
			dir.z - e->up.z * 10.0, 1.0};
	else if (key == PLUS)
		e->cam->dir = (t_vector){dir.x + n.x * 10.0, dir.y + n.y * 10.0, dir.z +
			n.z * 10.0, 1.0};
	else if (key == MINUS)
		e->cam->dir = (t_vector){dir.x - n.x * 10.0, dir.y - n.y * 10.0, dir.z -
			n.z * 10.0, 1.0};
}

void			translate_obj_pos(int key, t_vector r, t_vector n, t_env *e)
{
	t_obj		*obj;

	if (1 == e->is_obj_selected)
	{
		obj = e->hit_obj;
		if (key == LEFT)
			e->hit_obj->pos = (t_vector){obj->pos.x + r.x * 10.0,
				obj->pos.y + r.y * 10.0, obj->pos.z + r.z * 10.0, 1.0};
		else if (key == RIGHT)
			e->hit_obj->pos = (t_vector){obj->pos.x - r.x * 10.0, obj->pos.y
				- r.y * 10.0, obj->pos.z - r.z * 10.0, 1.0};
		else if (key == UP)
			e->hit_obj->pos = (t_vector){obj->pos.x + e->up.x * 10.0,
				obj->pos.y + e->up.y * 10.0, obj->pos.z + e->up.z * 10.0, 1.0};
		else if (key == DOWN)
			e->hit_obj->pos = (t_vector){obj->pos.x - e->up.x * 10.0,
				obj->pos.y - e->up.y * 10.0, obj->pos.z - e->up.z * 10.0, 1.0};
		else if (key == PLUS)
			e->hit_obj->pos = (t_vector){obj->pos.x + n.x * 10.0,
				obj->pos.y + n.y * 10.0, obj->pos.z + n.z * 10.0, 1.0};
		else if (key == MINUS)
			e->hit_obj->pos = (t_vector){obj->pos.x - n.x * 10.0, obj->pos.y -
				n.y * 10.0, obj->pos.z - n.z * 10.0, 1.0};
	}
}

void			translate(int key, t_env *e)
{
	t_vector	n;
	t_vector	r;

	repere(e, &n, &r);
	if (e->is_obj_selected == 1)
		translate_obj_pos(key, r, n, e);
	else
	{
		translate_cam_pos(key, r, n, e);
		translate_cam_dir(key, r, n, e);
	}
	if (key == R)
	{
		e->is_obj_selected = 0;
		e->hit_obj = NULL;
	}
	translate_light(key, r, n, e);
}
