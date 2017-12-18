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
#define EQ_TOLERANCE 1.0e-4

t_vector		torus_normal(t_obj *torus, t_vector p)
{
	t_vector normal;

	normal.x = 4.0 * p.x *  (p.x * p.x + p.y * p.y + p.z * p.z + torus->a * torus->a - torus->b * torus->b) - 8.0 * torus->a * torus->a * p.x;
	normal.y = 4.0 * p.y * (p.x * p.x + p.y * p.y + p.z * p.z + torus->a * torus->a - torus->b * torus->b) - 8.0 * torus->a * torus->a * p.y;
	normal.z = 4.0 * (p.x * p.x + p.y * p.y + p.z * p.z + torus->a * torus->a - torus->b * torus->b) * p.x;
	normalize(&normal);
	return (normal);
}

int			is_point_inside_torus(t_obj *torus, t_vector point)
{
	double t;
	double f;

	t = torus->a - sqrt(point.x * point .x + point.z * point.z);
	f = (t * t) + (point.y * point.y) - (torus->b * torus->b);
	return (f <= (double)EPSILON);

}

int			torus_solver_coef(t_obj *torus, t_ray r, double roots[4])
{
	t_polyn poly;
	t_vector dist;

	dist = r.pos;
	poly.a = prodscal(r.dir, r.dir) * prodscal(r.dir, r.dir) ;

	poly.b = 4.0 * prodscal(r.dir, r.dir) *  prodscal(dist , r.dir) ;

	poly.c = 2.0 * prodscal(r.dir, r.dir) * (normevectsquar(dist) + (torus->a * torus->a) - (torus->b * torus->b)) + (2.0 * prodscal(dist, r.dir) * 2.0 * prodscal(dist, r.dir)) - (4.0 * torus->a * torus->a * (r.dir.x * r.dir.x + r.dir.z * r.dir.z));

	poly.d = 2.0 * 2.0 * prodscal(dist, r.dir) * (normevectsquar(dist) + torus->a * torus->a  - torus->b * torus->b) -  8.0 * (torus->a * torus->a) * (dist.x * r.dir.x + dist.z * r.dir.z);

	poly.e = powf((normevectsquar(dist) + (torus->a * torus->a) - (torus->b * torus->b)), 2) - 4.0 * torus->a * torus->a * (dist.x * dist.x + dist.z * dist.z);

	return(quartic(poly, roots));
}

t_color			get_torus_texture_color(t_hit *inter, t_env *e)
{
	return (get_cylinder_texture_color(inter, e));
}
void	 append_torus(t_obj *torus, t_ray ray, t_hit **hit_list)
{
	t_ray r;
	t_hit *new;
	int num_sol;
	double  roots[4];
	t_vector point;
	int i;

	r.dir = objectdir_from_cameradir(ray.dir, torus->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, torus->center, torus->base);
	num_sol = torus_solver_coef(torus, r,  &roots[0]);
	
	i = -1;
	while (++i < num_sol)
	{
	
		//if (roots[i] > 0.0)
		//{
			point = addvect(r.pos, scalevect(roots[i], r.dir));
			if (roots[i] > (double)TOLERANCE) //TRUE == is_point_inside_torus(torus, point))
			{
				if (!(new = (t_hit*)malloc(sizeof(t_hit))))
					err_exit("Unable to allocate\n");

			new->point = point;
			new->t = roots[i];
			//new->normal = (t_vector){((1.0 - (torus->a / sqrtf(new->point.x * new->point.x + new->point.z * new->point.z))) * new->point.x), (1.0 - (torus->a / sqrtf(new->point.x * new->point.x + new->point.z * new->point.z))) * new->point.y, new->point.z };

//new->normal = (t_vector){((1.0 - (torus->a / sqrtf(new->point.x * new->point.x + new->point.z * new->point.z))) * new->point.x), new->point.y, (1.0 - (torus->a / sqrtf(new->point.x * new->point.x + new->point.z * new->point.z))) * new->point.z};

			//normalize(&new->normal);
			new->normal = torus_normal(torus, point);
			new->obj = torus;
		//new->in_ray = ray;
			new->displacement = normevectsquar(scalevect(roots[i], r.dir));
			new->ray_origin = r.pos;
			new->next = NULL;
			add_point_to_intersection_list(hit_list, new);
			}
		//}
	}
}

