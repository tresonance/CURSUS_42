/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:54:44 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 03:20:34 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

void	current_ray(double x, double y, t_env *e, t_ray *ray)
{
	double	xindent;
	double	yindent;
	

	init_camera_axes(e->cam);

	xindent = (2.0 * ((x + 0.5) /(double) WIDTH) - 1.0)  * ((double)WIDTH) / HEIGHT;
	yindent = (1.0 - 2.0 * ((y + 0.5) / (double)HEIGHT));
	
	ray->pos.x = e->cam->pos.x;
	ray->pos.y = e->cam->pos.y;
	ray->pos.z = e->cam->pos.z;
	
	ray->type = PRIMARY_RAY;
	ray->obj_from = NULL;
	//CAMERA TO WORLD	
	ray->dir.x = (double)FOC * e->cam->dir.x + yindent * e->cam->up.x + xindent * e->cam->right.x;
	ray->dir.y = (double)FOC * e->cam->dir.y + yindent * e->cam->up.y + xindent * e->cam->right.y;
	ray->dir.z = (double)FOC * e->cam->dir.z + yindent * e->cam->up.z + xindent * e->cam->right.z;
	normalize(&ray->dir);
}


