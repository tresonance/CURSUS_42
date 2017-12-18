/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_mouvement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:52:43 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 01:27:32 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

//CUBOID MOVEMENT 

double		radian_from_degree(double angle_degree)
{
	return (M_PI * angle_degree / 180.0);
}

void		translate_obj(t_obj *obj, double tx, double ty, double tz)
{
	obj->center.x += tx;
	obj->center.y += ty;
	obj->center.z += tz;
}

void		move_obj(t_obj *obj, double mx, double my, double mz)
{
	t_vector tr;
	tr = (t_vector){mx, my, mz};
	tr = subvect(tr, obj->center);
	translate_obj(obj, tr.x, tr.y, tr.z);
}

void		rotate_x_obj(t_obj *obj, double angle_degree)
{
	double alpha;

	alpha = radian_from_degree(angle_degree);

	obj->base.rdir = (t_vector){obj->base.rdir.x, obj->base.rdir.y * cosf(alpha) - obj->base.rdir.z * sinf(alpha), obj->base.rdir.y * sinf(alpha) + obj->base.rdir.z * cosf(alpha)};

	obj->base.sdir = (t_vector){obj->base.sdir.x, obj->base.sdir.y * cosf(alpha) - obj->base.sdir.z * sinf(alpha), obj->base.sdir.y * sinf(alpha) + obj->base.sdir.z * cosf(alpha)};

	obj->base.tdir = (t_vector){obj->base.tdir.x, obj->base.tdir.y * cosf(alpha) - obj->base.tdir.z * sinf(alpha), obj->base.tdir.y * sinf(alpha) + obj->base.tdir.z * cosf(alpha)};
	normalize(&obj->base.rdir);
	normalize(&obj->base.sdir);
	normalize(&obj->base.tdir);
}

void		rotate_y_obj(t_obj *obj, double angle_degree)
{
	double alpha;

	alpha = radian_from_degree(angle_degree);

	obj->base.rdir = (t_vector){obj->base.rdir.x * cosf(alpha) + obj->base.rdir.z * sinf(alpha), obj->base.rdir.y, -obj->base.rdir.x * sinf(alpha) + obj->base.rdir.z * cosf(alpha)};

	obj->base.sdir = (t_vector){obj->base.sdir.x * cosf(alpha) + obj->base.sdir.z * sinf(alpha), obj->base.sdir.y, -obj->base.sdir.x * sinf(alpha) + obj->base.sdir.z * cosf(alpha)};

	obj->base.tdir = (t_vector){obj->base.tdir.x * cosf(alpha) + obj->base.tdir.z * sinf(alpha), obj->base.tdir.y, -obj->base.tdir.x * sinf(alpha) + obj->base.tdir.z * cosf(alpha)};
	normalize(&obj->base.rdir);
	normalize(&obj->base.sdir);
	normalize(&obj->base.tdir);
}

void		rotate_z_obj(t_obj *obj, double angle_degree)
{
	double alpha;

	alpha = radian_from_degree(angle_degree);

	obj->base.rdir = (t_vector){obj->base.rdir.x * cosf(alpha) - obj->base.rdir.y * sinf(alpha), obj->base.rdir.x * sinf(alpha) + obj->base.rdir.y * cosf(alpha), obj->base.rdir.z};

	obj->base.sdir = (t_vector){obj->base.sdir.x * cosf(alpha) - obj->base.sdir.y * sinf(alpha), obj->base.sdir.x * sinf(alpha) + obj->base.sdir.y * cosf(alpha), obj->base.sdir.z};

	obj->base.tdir = (t_vector){obj->base.tdir.x * cosf(alpha) - obj->base.tdir.y * sinf(alpha), obj->base.tdir.x * sinf(alpha) + obj->base.tdir.y * cosf(alpha), obj->base.tdir.z};
	normalize(&obj->base.rdir);
	normalize(&obj->base.sdir);
	normalize(&obj->base.tdir);
}
