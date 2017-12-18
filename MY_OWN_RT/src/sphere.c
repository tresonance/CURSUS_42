/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:57:24 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 07:06:08 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc -Wall -Wextra -Werror -lft -L libft -lmlx -L ./minilibx -framework OpenGL //-framework AppKit libft/libft.a src/*.c

#include "../includes/rt.h"

/*int		is_point_inside_sphere(t_obj *sphere, t_vector point)
{
	double radius_squar;

	radius_squar = normevectsquar(subvect(point, sphere->center));
	return (radius_squar <= (sphere->radius * sphere->radius));
}*/

t_vector	calcul_sphere_normal(t_obj **sphere, t_vector point, double t, t_ray r)
{
	t_vector normal;

	(void)r;
	(void)t;
	(void)sphere;
	normal = point;
	normalize(&normal);
	return (normal);
}

static void	set_second_degre_coef(t_obj **sphere, t_ray r,
		t_vector dist, double *coef)
{
	coef[0] = prodscal(r.dir, r.dir);
	coef[1] = 2.0 * prodscal(r.dir, dist);
	coef[2] = prodscal(dist, dist) - ((*sphere)->radius * (*sphere)->radius);
}

static double	convert_ray_and_solve(t_obj **sphere, t_ray ray, t_ray *r)
{
	t_vector	dist;
	double		coef[3];

	r->dir = objectdir_from_cameradir(ray.dir, (*sphere)->base);
	normalize(&(r->dir));
	r->pos = objectpoint_from_camerapoint(ray.pos, (*sphere)->center,
			(*sphere)->base);
	normalize(&(*sphere)->axe);
	dist = r->pos;
	set_second_degre_coef(sphere, *r, dist, &coef[0]);
	return(cut_obj(&coef[0], *sphere, r->dir, r->pos));
}

void		append_sphere2(t_obj *sphere, t_ray ray, t_hit **hit_list)
{
	double coef[3];
	t_vector dist;
	int num_sol;
	double roots[2];
	t_hit *new;
	int	i;
	t_vector point;
	t_ray r;

	r.dir = objectdir_from_cameradir(ray.dir, sphere->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, sphere->center, sphere->base);


	dist = r.pos;
	coef[0] = prodscal(r.dir, r.dir);
	coef[1] = 2.0 * prodscal(r.dir, dist);
	coef[2] = prodscal(dist, dist) - (sphere->radius * sphere->radius);
	num_sol = second_degre(coef, roots);
	i = -1;
	while (++i < num_sol)
	{
		if (roots[i] > (double)EPSILON && roots[i] < (double)INFINI)
		{
			point = addvect(r.pos , scalevect(roots[i], r.dir));
			//we found an interay.ection with the infinitely-extended lateray.l
			//but the z-component must be + oray.-zdis
			if (fabs(point.y) <= sphere->zdisk  && is_hit_point_already_inside(point, *hit_list) == FALSE)
			{
				if (!(new = (t_hit*)malloc(sizeof(t_hit))))
					err_exit("Unable to allocate\n");
				new->t = roots[i];
				new->point = point;
				new->obj = sphere;
				//new->in_ray = ray;
				new->displacement = normevectsquar(scalevect(roots[i], r.dir));
				new->next = NULL;
				new->normal = point;
				normalize(&new->normal);
				new->ray_origin = r.pos;
				add_point_to_intersection_list(hit_list, new);
			}
		}
	}
}

void		append_sphere_(t_obj *sphere, t_ray ray, t_hit **hit_list, t_ray r)
{
	//double coef[3];
	//t_vector dist;
	//int num_sol;
	//double roots[2];
	t_hit *new;
	//int	i;
	t_vector point;
	t_vector normal;
	double		t;
	//t_ray r;

	/*r.dir = objectdir_from_cameradir(ray.dir, sphere->base);
	  normalize(&(r.dir));
	  r.pos = objectpoint_from_camerapoint(ray.pos, sphere->center, sphere->base);*/


	/*dist = r.pos;
	  coef[0] = prodscal(r.dir, r.dir);
	  coef[1] = 2.0 * prodscal(r.dir, dist);
	  coef[2] = prodscal(dist, dist) - (sphere->radius * sphere->radius);
	  num_sol = second_degre(coef, roots);
	  i = -1;*/
	//while (++i < num_sol)
	//{
	t = convert_ray_and_solve(&sphere, ray, &r);
	if (t > 0.0f  && t < (double)INFINI)
	{
		point = addvect(r.pos , scalevect(t, r.dir));
		//we found an interay.ection with the infinitely-extended lateray.l
		//but the z-component must be + oray.-zdis
		//if (fabs(point.y) <= sphere->zdisk  && is_hit_point_already_inside(point, *hit_list) == FALSE)
		//	{
		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate\n");
		new->displacement = normevectsquar(scalevect(t, r.dir));
		//normal = calcul_cylin_normal(&sphere, point, t, r);
		normal = point;
		set_inter_info1(&new, t, normal, point);
		set_inter_info2(&new, &sphere, ray, ray.pos);
		add_point_to_intersection_list(hit_list, new);
		//}
	}
	//}
}

void		append_sphere(t_obj *sphere, t_ray ray, t_hit **hit_list)
{
	t_ray r;

	r.dir = (t_vector){0.0, 0.0, 0.0 };
	r.pos = (t_vector){0.0, 0.0, 0.0 };
	append_sphere_(sphere, ray, hit_list, r);
}
