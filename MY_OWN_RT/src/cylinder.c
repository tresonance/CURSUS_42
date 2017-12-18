/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:47:10 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 13:40:01 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void			set_second_degre_coef(t_obj **cylin, t_ray r,
		t_vector dist, double *coef)
{
	coef[0] = prodscal(r.dir, r.dir) -
		pow(prodscal((*cylin)->axe, r.dir), 2);
	coef[1] = 2.0 * (prodscal(dist, r.dir) -
			(prodscal((*cylin)->axe, dist) * prodscal((*cylin)->axe, r.dir)));
	coef[2] = prodscal(dist, dist) -
		pow(prodscal((*cylin)->axe, dist), 2) - ((*cylin)->radius *
				(*cylin)->radius);
}

static double			convert_ray_and_solve(t_obj **cylin, t_ray ray , t_ray *r)
{
	t_vector		dist;
	double			coef[3];

	r->dir = objectdir_from_cameradir(ray.dir, (*cylin)->base);
	normalize(&(r->dir));
	r->pos = objectpoint_from_camerapoint(ray.pos, (*cylin)->center,
			(*cylin)->base);
	normalize(&(*cylin)->axe);
	dist = r->pos;
	set_second_degre_coef(cylin, *r, dist, &coef[0]);
	return(cut_obj(&coef[0], *cylin, r->dir, r->pos));
}

t_vector		calcul_cylin_normal(t_obj **cylin, t_vector point, double t, t_ray r)
{
	t_vector		dist;
	t_vector		left;
	t_vector		right;
	double			m;
	t_vector		normal;

	dist = r.pos;
	m = t * prodscal(r.dir, (*cylin)->axe) + prodscal(dist, (*cylin)->axe);
	left = subvect(point, (*cylin)->center);
	right = scalevect((1 + pow(tan((*cylin)->radius), 2)) * m, (*cylin)->axe);
	normal = subvect(left, right);
	normalize(&normal);
	return (normal);
}

static void			append_cylinder_lateral(t_obj *cylin, t_ray ray,
		t_hit **hit_list, t_ray r)
{
	t_vector		normal;
	t_hit			*new;
	t_vector		point;
	double t;

	t = convert_ray_and_solve(&cylin, ray, &r);
		if (t > 0.0f && t < (double)INFINI)
		{
			point = addvect(r.pos, scalevect(t, r.dir));
			if (!(new = (t_hit*)malloc(sizeof(t_hit))))
				err_exit("Unable to allocate\n");
			new->displacement = normevectsquar(scalevect(t, r.dir));
			normal = calcul_cylin_normal(&cylin, point, t, r);
			set_inter_info1(&new, t, normal, point);
			set_inter_info2(&new, &cylin, ray, ray.pos);
			add_point_to_intersection_list(hit_list, new);
		}
}

void				append_cylinder(t_obj *cylin, t_ray ray, t_hit **hit_list)
{
	t_ray			r;

	r.dir = (t_vector){0.0, 0.0, 0.0 };
	r.pos = (t_vector){0.0, 0.0, 0.0 };
	append_cylinder_lateral(cylin, ray, hit_list, r);
}
