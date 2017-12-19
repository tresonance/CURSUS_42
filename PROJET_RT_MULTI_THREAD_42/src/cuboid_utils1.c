/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuboid_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:08:12 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 11:50:43 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void			append_cuboid_inter_pa(t_obj *cub, t_ray ray, t_hit **hit)
{
	t_ray		r;
	double		t;
	t_vector	point;
	t_hit		*new;

	if (cub->right == 0)
		return ;
	r.dir = objectdir_from_cameradir(ray.dir, cub->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, cub->center, cub->base);
	if (fabs(r.dir.x) <= (double)EPSILON)
		return ;
	t = (cub->a - r.pos.x) / r.dir.x;
	if (t <= (double)EPSILON)
		return ;
	point = addvect(r.pos, scalevect(t, r.dir));
	if (TRUE == is_point_lying_inside_cuboid(&cub, point, &hit))
	{
		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate\n");
		new->displacement = normevectsquar(scalevect(t, r.dir));
		set_inter_info1(&new, t, cub->base.rdir, point);
		set_inter_info2(&new, &cub, ray, ray.pos);
		add_point_to_intersection_list(hit, new);
	}
}

void			append_cuboid_inter_ma(t_obj *cub, t_ray ray, t_hit **hit)
{
	t_ray		r;
	double		t;
	t_vector	point;
	t_hit		*new;

	if (cub->left == 0)
		return ;
	r.dir = objectdir_from_cameradir(ray.dir, cub->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, cub->center, cub->base);
	if (fabs(r.dir.x) <= (double)EPSILON)
		return ;
	t = (-1.0 * cub->a - r.pos.x) / r.dir.x;
	if (t <= (double)EPSILON)
		return ;
	point = addvect(r.pos, scalevect(t, r.dir));
	if (TRUE == is_point_lying_inside_cuboid(&cub, point, &hit))
	{
		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate\n");
		new->displacement = normevectsquar(scalevect(t, r.dir));
		set_inter_info1(&new, t, (t_vector){-1.0, 0.0, 0.0 }, point);
		set_inter_info2(&new, &cub, ray, ray.pos);
		add_point_to_intersection_list(hit, new);
	}
}

void			append_cuboid_inter_pb(t_obj *cub, t_ray ray, t_hit **hit)
{
	t_ray		r;
	double		t;
	t_vector	point;
	t_hit		*new;

	if (cub->up == 0)
		return ;
	r.dir = objectdir_from_cameradir(ray.dir, cub->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, cub->center, cub->base);
	if (fabs(r.dir.y) <= (double)EPSILON)
		return ;
	t = (cub->b - r.pos.y) / r.dir.y;
	if (t <= (double)EPSILON)
		return ;
	point = addvect(r.pos, scalevect(t, r.dir));
	if (TRUE == is_point_lying_inside_cuboid(&cub, point, &hit))
	{
		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate\n");
		new->displacement = normevectsquar(scalevect(t, r.dir));
		set_inter_info1(&new, t, cub->base.sdir, point);
		set_inter_info2(&new, &cub, ray, ray.pos);
		add_point_to_intersection_list(hit, new);
	}
}

void			append_cuboid_inter_mb(t_obj *cub, t_ray ray, t_hit **hit)
{
	t_ray		r;
	double		t;
	t_vector	point;
	t_hit		*new;

	if (cub->down == 0)
		return ;
	r.dir = objectdir_from_cameradir(ray.dir, cub->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, cub->center, cub->base);
	if (fabs(r.dir.y) <= (double)EPSILON)
		return ;
	t = (-cub->b - r.pos.y) / r.dir.y;
	if (t <= (double)EPSILON)
		return ;
	point = addvect(r.pos, scalevect(t, r.dir));
	if (TRUE == is_point_lying_inside_cuboid(&cub, point, &hit))
	{
		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate\n");
		new->displacement = normevectsquar(scalevect(t, r.dir));
		set_inter_info1(&new, t, (t_vector){0.0, -1.0, 0.0 }, point);
		set_inter_info2(&new, &cub, ray, ray.pos);
		add_point_to_intersection_list(hit, new);
	}
}
