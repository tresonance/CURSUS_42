/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:53:20 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/15 23:53:33 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

void	 append_plane(t_obj *plane, t_ray ray, t_hit **hit_list)
{
	t_vector	dist;
	double 		t;
	t_hit		*new;
	double		deno;

        dist = subvect(ray.pos, plane->center);
	normalize(&plane->axe);
	deno =  prodscal(plane->axe, ray.dir);
	//if (fabs(deno) < (double)TOLERANCE)
	//	return ;
        t = -1.0 * prodscal(plane->axe, dist) / deno;
	if (t > (double)EPSILON)
	{
		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate memory\n");

		if (deno > 0.0)
                        new->normal = scalevect(-1.0, plane->axe);
                else    
                        new->normal = plane->axe;
		normalize(&new->normal);
		new->t = t;
		new->point = addvect(ray.pos, scalevect(t, ray.dir));
		new->displacement = normevectsquar(scalevect(t, ray.dir));
		new->obj = plane;
		new->ray_origin = ray.pos;
		new->next = NULL;
		add_point_to_intersection_list(hit_list, new);
	}
}

