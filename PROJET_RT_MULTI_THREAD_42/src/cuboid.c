/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuboid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:46:50 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 11:10:06 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int			is_point_inside_cuboid(t_obj *cub, t_vector point)
{
	return ((fabs(point.x) <= (cub->a) + (double)EPSILON)
			&& (fabs(point.y) <= (cub->b) + (double)EPSILON)
			&& (fabs(point.z) <= (cub->c) + (double)EPSILON));
}

int			is_point_lying_inside_cuboid(t_obj **cub, t_vector point,
		t_hit ***hit)
{
	if (TRUE == is_point_inside_cuboid(*cub, point) &&
			FALSE == is_hit_point_already_inside(point, **hit))
		return (TRUE);
	return (FALSE);
}

void		append_cuboid(t_obj *cub, t_ray ray, t_hit **hit)
{
	append_cuboid_inter_pa(cub, ray, hit);
	append_cuboid_inter_ma(cub, ray, hit);
	append_cuboid_inter_pb(cub, ray, hit);
	append_cuboid_inter_mb(cub, ray, hit);
	append_cuboid_inter_pc(cub, ray, hit);
	append_cuboid_inter_mc(cub, ray, hit);
}
