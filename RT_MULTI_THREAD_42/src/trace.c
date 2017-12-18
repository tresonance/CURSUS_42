/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:59:24 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 06:24:05 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"
#define SHIFT 0.001


t_color			raytrace(t_ray ray , int depth, t_env *e, t_hit *inter)
{
	int outside;
	t_color color;

	color = (t_color){0.0, 0.0, 0.0 };;
	
		if (depth < MAX_DEPTH && inter->t < MAX_DIST)
		{
			if (!ft_strcmp(inter->obj->name, "\tchessboard"))
				chessboard_color(inter->obj, inter);

			color = calculate_matte(inter,e);
			fresnel(inter, ray, e);
			outside = (prodscal(ray.dir , inter->normal) < 0.0);

			if (inter->obj->type[0] != 0)
			{
				e->refl = reflect(inter, ray);
				e->refl.pos = outside ? addvect(inter->point, scalevect(SHIFT, inter->normal))  : subvect(inter->point, scalevect(SHIFT, inter->normal));
 
				color = addcol(color, scalcol(e->kr, tracer(e->refl, depth + 1, e)));
			}
			if (inter->obj->type[1] != 0)
			{
				//outside = (prodscal(ray.dir , inter->normal) < 0.0);
				e->refrcolor = (t_color){0.0, 0.0, 0.0};
				if (e->kr < 1.0)
				{
					e->refr = refract(inter, ray, e);
					e->refr.pos = outside ? addvect(inter->point, scalevect(SHIFT, inter->normal))  : subvect(inter->point, scalevect(SHIFT, inter->normal));
					color = addcol(color, scalcol(1.0 - e->kr,tracer(e->refr, depth + 1, e)));
				}
			}
		}
	return (color);
}


t_color		tracer(t_ray ray, int depth, t_env *e)
{
	t_color color;
	int num_hit;
	t_hit *inter;

	color = (t_color){0.0, 0.0, 0.0};;
	inter = NULL;
	num_hit = findclosest_intersection(e, ray,  &inter);
	if (num_hit == 0)
		return (e->scene->background);
	else if (num_hit > 0)
	{
		if (inter->obj->tag > 0 && e->texture_arr)
		{
			inter->obj->matte = get_texture_color(inter, e);
			inter->obj->glossy = inter->obj->matte;
			//inter->obj->glossy = (t_color){1.0, 1.0, 1.0};
			color = calculate_matte(inter, e);
		}
		else
		{
			color = raytrace(ray, depth, e, inter);
		}
	}	
	if (inter)
		ft_memdel((void**)&inter);
	return (color);
}
