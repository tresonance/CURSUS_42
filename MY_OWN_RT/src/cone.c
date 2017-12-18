/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:45:57 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 12:57:27 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static void			set_second_degre_coef(t_obj **cone, t_ray r,
		t_vector dist, double *coef)
{
	coef[0] = prodscal(r.dir, r.dir) - (1 + pow(tan((*cone)->radius), 2)) *
		pow(prodscal(r.dir, (*cone)->axe), 2);
	coef[1] = 2 * (prodscal(r.dir, dist) - (1 + pow(tan((*cone)->radius), 2))
			* prodscal(r.dir, (*cone)->axe) * prodscal(dist, (*cone)->axe));
	coef[2] = prodscal(dist, dist) -
		(1 + pow(tan((*cone)->radius), 2)) * pow(prodscal(dist,
					(*cone)->axe), 2);
}

static double	convert_ray_and_solve(t_obj **cone, t_ray ray , t_ray *r)
{
	t_vector dist;
	double	coef[3];

	r->dir = objectdir_from_cameradir(ray.dir, (*cone)->base);
	normalize(&(r->dir));
	r->pos = objectpoint_from_camerapoint(ray.pos, (*cone)->center,
			(*cone)->base);
	normalize(&(*cone)->axe);
	dist = r->pos;
	set_second_degre_coef(cone, *r, dist, &coef[0]);
	return(cut_obj(&coef[0], *cone, r->dir, r->pos));
}


/*static int			convert_ray_and_solve(t_obj **cone, t_ray ray,
  double *roots, t_ray *r)
  {
  int				num_sol;
  t_vector		dist;
  double			coef[3];

  num_sol = 0;
  r->dir = objectdir_from_cameradir(ray.dir, (*cone)->base);
  normalize(&(r->dir));
  r->pos = objectpoint_from_camerapoint(ray.pos, (*cone)->center,
  (*cone)->base);
  normalize(&(*cone)->axe);
  dist = r->pos;
  set_second_degre_coef(cone, *r, dist, &coef[0]);
  num_sol = second_degre(&coef[0], roots);
  return (num_sol);
  }*/

t_vector		calcul_cone_normal(t_obj **cone, t_vector point, double t, t_ray r)
{
	t_vector		dist;
	t_vector		left;
	t_vector		right;
	double			m;
	t_vector		normal;

	dist = r.pos;
	m = t * prodscal(r.dir, (*cone)->axe) + prodscal(dist, (*cone)->axe);
	left = subvect(point, (*cone)->center);
	right = scalevect((1 + pow(tan((*cone)->radius), 2)) * m, (*cone)->axe);
	normal = subvect(left, right);
	normalize(&normal);
	return (normal);
}

static void			append_cone_lateral(t_obj *cone, t_ray ray,
		t_hit **hit_list, t_ray r)
{
	//double			roots[2];
	t_vector		point;
	//int				i[2];
	t_hit			*new;
	t_vector		normal;
	double			t;

	t = convert_ray_and_solve(&cone, ray, &r);
	//i[0] = -1;
	//while (++i[0] < i[1])
	//	{
	//if (roots[i[0]] <= (double)EPSILON)
	//	return ;
	//point = addvect(r.pos, scalevect(roots[i[0]], r.dir));
	if (t > 0.0f && t < (double)INFINI)
	{
		point = addvect(r.pos, scalevect(t, r.dir));

		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate\n");
		new->displacement = normevectsquar(scalevect(t, r.dir));
		normal = calcul_cone_normal(&cone, point, t, r);
		set_inter_info1(&new, t, normal, point);
		set_inter_info2(&new, &cone, ray, ray.pos);
		add_point_to_intersection_list(hit_list, new);
	}
	//}
}

void				append_cone(t_obj *cone, t_ray ray, t_hit **hit_list)
{
	t_ray			r;

	r.dir = (t_vector){0.0, 0.0, 0.0 };
	r.pos = (t_vector){0.0, 0.0, 0.0 };
	append_cone_lateral(cone, ray, hit_list, r);
}
