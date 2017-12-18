/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brick.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:41:53 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/19 15:31:36 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#define THICKNESS 10

static int				brick_contains(t_obj *brick, t_vector point)
{
	if ((point.x > -brick->a + THICKNESS && point.x < brick->a - THICKNESS
		&& point.y > THICKNESS / 2 && point.y < brick->b - THICKNESS)
		|| (point.x > -brick->a + THICKNESS && point.x < brick->a - THICKNESS
		&& point.y < -THICKNESS / 2 && point.y > -brick->b + THICKNESS))
		return (FALSE);
	return (TRUE);
}

static void			function_to_call(t_obj *brick, t_ray ray, t_hit **hit_list)
{
	append_cuboid_inter_pa(brick, ray, hit_list);
	append_cuboid_inter_ma(brick, ray, hit_list);
	append_cuboid_inter_pb(brick, ray, hit_list);
	append_cuboid_inter_mb(brick, ray, hit_list);
	append_cuboid_inter_pc(brick, ray, hit_list);
}

static int				is_point_inside_brick(t_obj **brick, t_vector point,
		t_hit ***hit_list)
{
	if (TRUE == is_point_inside_cuboid(*brick, point) &&
					FALSE == is_hit_point_already_inside(point, **hit_list)
					&& brick_contains(*brick, point))
		return (TRUE);
	return (FALSE);
}

void			append_brick(t_obj *brick, t_ray ray, t_hit **hit_list)
{
	t_ray		r;
	double		t;
	t_hit		*new;
	t_vector	point;

	function_to_call(brick, ray, hit_list);
	if (brick->front == 0)
		return ;
	r.dir = objectdir_from_cameradir(ray.dir, brick->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, brick->center, brick->base);
	if (fabs(r.dir.z) <= (double)EPSILON)
		return ;
	if ((t = (-brick->c - r.pos.z) / r.dir.z) && t > (double)EPSILON)
	{
		point = addvect(r.pos, scalevect(t, r.dir));
		if (TRUE == is_point_inside_brick(&brick, point, &hit_list))
		{
			if (!(new = (t_hit*)malloc(sizeof(t_hit))))
				err_exit("Unable to allocate\n");
			set_inter_info1(&new, t, (t_vector){0.0, 0.0, -1.0}, point);
			set_inter_info2(&new, &brick, ray, ray.pos);
			add_point_to_intersection_list(hit_list, new);
		}
	}
}
