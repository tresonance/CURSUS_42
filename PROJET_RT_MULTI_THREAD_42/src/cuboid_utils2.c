/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuboid_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 11:54:00 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 11:54:50 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			append_cuboid_inter_pc(t_obj *cub, t_ray ray, t_hit **hit)
{
	t_ray		r;
	double		t;
	t_vector	point;
	t_hit		*new;

	if (cub->back == 0)
		return ;
	r.dir = objectdir_from_cameradir(ray.dir, cub->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, cub->center, cub->base);
	if (fabs(r.dir.z) <= (double)EPSILON)
		return ;
	t = (cub->c - r.pos.z) / r.dir.z;
	if (t <= (double)EPSILON)
		return ;
	point = addvect(r.pos, scalevect(t, r.dir));
	if (is_point_lying_inside_cuboid(&cub, point, &hit))
	{
		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate\n");
		new->displacement = normevectsquar(scalevect(t, r.dir));
		set_inter_info1(&new, t, cub->base.tdir, point);
		set_inter_info2(&new, &cub, ray, ray.pos);
		add_point_to_intersection_list(hit, new);
	}
}

void			append_cuboid_inter_mc(t_obj *cub, t_ray ray, t_hit **hit)
{
	t_ray		r;
	double		t;
	t_vector	point;
	t_hit		*new;

	if (cub->front == 0)
		return ;
	r.dir = objectdir_from_cameradir(ray.dir, cub->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, cub->center, cub->base);
	if (fabs(r.dir.z) <= (double)EPSILON)
		return ;
	t = (-cub->c - r.pos.z) / r.dir.z;
	if (t <= (double)EPSILON)
		return ;
	point = addvect(r.pos, scalevect(t, r.dir));
	if (is_point_lying_inside_cuboid(&cub, point, &hit))
	{
		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate\n");
		set_inter_info1(&new, t, (t_vector){0.0, 0.0, -1.0}, point);
		set_inter_info2(&new, &cub, ray, ray.pos);
		add_point_to_intersection_list(hit, new);
	}
}
