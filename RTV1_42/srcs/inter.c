/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 10:06:44 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/11 02:00:16 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

double	sphere_inter(t_obj *obj, t_ray *ray)
{
	double		t;
	t_solver	s;

	s.dist = subvect(&obj->pos, &ray->pos);
	s.a = prodscal(&ray->dir, &ray->dir);
	s.b = 2.0 * prodscal(&ray->dir, &s.dist);
	s.c = prodscal(&s.dist, &s.dist) - (obj->size * obj->size);
	t = solver(&s);
	return (t);
}

double	cylinder_inter(t_obj *obj, t_ray *ray)
{
	double		t;
	t_solver	s;

	s.dist = subvect(&obj->pos, &ray->pos);
	normalize(&obj->rot);
	s.a = prodscal(&ray->dir, &ray->dir) -
		pow(prodscal(&obj->rot, &ray->dir), 2);
	s.b = 2.0 * (prodscal(&s.dist, &ray->dir) -
			(prodscal(&obj->rot, &s.dist) * prodscal(&obj->rot, &ray->dir)));
	s.c = prodscal(&s.dist, &s.dist) -
		pow(prodscal(&obj->rot, &s.dist), 2) - obj->size * obj->size;
	t = solver(&s);
	return (t);
}

double	cone_inter(t_obj *obj, t_ray *ray)
{
	double		t;
	t_solver	s;
	double		m;

	m = 0;
	s.dist = subvect(&obj->pos, &ray->pos);
	normalize(&obj->rot);
	s.a = prodscal(&ray->dir, &ray->dir) - (1 + pow(tan(obj->size), 2)) *
		pow(prodscal(&ray->dir, &obj->rot), 2);
	s.b = 2 * (prodscal(&ray->dir, &s.dist) - (1 + pow(tan(obj->size), 2))
			* prodscal(&ray->dir, &obj->rot) * prodscal(&s.dist, &obj->rot));
	s.c = prodscal(&s.dist, &s.dist) -
		(1 + pow(tan(obj->size), 2)) * pow(prodscal(&s.dist, &obj->rot), 2);
	t = solver(&s);
	return (t);
}

double	plane_inter(t_obj *obj, t_ray *ray)
{
	double		t;
	t_solver	s;

	s.dist = subvect(&obj->pos, &ray->pos);
	t = -1.0 * prodscal(&obj->rot, &s.dist) / prodscal(&obj->rot, &ray->dir);
	if (t < 0.0001)
		t = -1;
	return (t);
}
