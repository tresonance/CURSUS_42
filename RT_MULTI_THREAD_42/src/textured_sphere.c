/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:59:06 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 08:22:57 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"
#define USCALE 0.8
#define VSCALE 0.8
#define LARGEUR_BANDE 5.0

t_color		get_sphere_texture_color(t_hit *inter, t_env *e)
{
	//t_color color;
	float u;
	float v;
	t_vector vp;
	t_texture *tex;
	
	tex = e->texture_arr[inter->obj->tag - 1];
	
	u = 0.5 + (atan2(inter->normal.y,inter->normal.x) / (2 * M_PI));
	v = 0.5 - (asin(inter->normal.z) / M_PI);
	inter->normal = objectdir_from_cameradir(inter->normal, inter->obj->base);
	vp = scalevect(inter->obj->radius, inter->normal);//subvect(inter->point, inter->obj->center));
normalize(&vp);
	float phi = acosf(-1.0 * prodscal(vp, inter->obj->base.sdir));
	
	v = phi * VSCALE * (1.0 / M_PI);
	float theta = (acosf(prodscal(inter->obj->base.rdir, vp) / sinf( phi ))) * (0.5f / M_PI);
	if (prodscal(inter->obj->base.tdir, vp) >= 0.0)
		u = (1.0 - theta) *  USCALE;
	else
		u = theta * USCALE;
	return (texture_color(e, inter, u, v));

	//color = texture_rgb(u * tex->width, v * tex->height, tex);
	//return (color);
}
