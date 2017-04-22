/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 08:22:23 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:15:12 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

double	solver(t_solver *s)
{
	s->delta = s->b * s->b - 4.0 * s->a * s->c;
	if (s->delta < 0)
		return (-1.0);
	s->t1 = 0.5 * (-1.0 * s->b - sqrtf(s->delta)) / ((double)s->a);
	s->t2 = 0.5 * (-1.0 * s->b + sqrtf(s->delta)) / ((double)s->a);
	if (s->t1 >= 0 && s->t2 >= 0)
		return ((s->t1 < s->t2) ? s->t1 : s->t2);
	else if (s->t1 * s->t2 <= 0.0)
		return ((s->t1 >= 0.0) ? s->t1 : s->t2);
	else
		return (-1);
}

void	get_hit_point_info1(t_hit *hit_point, t_obj *obj, t_ray *ray)
{
	double		m;
	t_vector	dist;
	t_vector	left;
	t_vector	right;

	if (ft_strcmp(obj->name, "	sphere") == 0)
		hit_point->normal = subvect(&obj->pos, &hit_point->point);
	if (ft_strcmp(obj->name, "	cylinder") == 0)
	{
		dist = subvect(&obj->pos, &ray->pos);
		m = hit_point->t * prodscal(&ray->dir, &obj->rot) +
			prodscal(&dist, &obj->rot);
		left = subvect(&obj->pos, &hit_point->point);
		right = scalevect(m, &obj->rot);
		hit_point->normal = subvect(&right, &left);
	}
}

void	get_hit_point_info2(t_hit *hit_point, t_obj *obj, t_ray *ray)
{
	double		m;
	t_vector	dist;
	t_vector	left;
	t_vector	right;

	if (ft_strcmp(obj->name, "	cone") == 0)
	{
		dist = subvect(&obj->pos, &ray->pos);
		m = hit_point->t * prodscal(&ray->dir, &obj->rot) +
			prodscal(&dist, &obj->rot);
		left = subvect(&obj->pos, &hit_point->point);
		right = scalevect((1 + pow(tan(obj->size), 2)) * m, &obj->rot);
		hit_point->normal = subvect(&right, &left);
	}
	if (ft_strcmp(obj->name, "	plane") == 0)
	{
		if (prodscal(&ray->dir, &obj->rot) > 0.0)
			hit_point->normal = scalevect(-1.0, &obj->rot);
		else
			hit_point->normal = obj->rot;
	}
}

void	get_hit_point_info(t_hit *hit_point, t_obj *obj, t_ray *ray)
{
	hit_point->ray_origin = ray;
	hit_point->point.x = ray->pos.x + hit_point->t * ray->dir.x;
	hit_point->point.y = ray->pos.y + hit_point->t * ray->dir.y;
	hit_point->point.z = ray->pos.z + hit_point->t * ray->dir.z;
	get_hit_point_info1(hit_point, obj, ray);
	get_hit_point_info2(hit_point, obj, ray);
	normalize(&hit_point->normal);
}
