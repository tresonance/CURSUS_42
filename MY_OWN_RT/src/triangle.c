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

t_vector	triangle_normal(t_obj *triangle)
{
	t_vector v0v1;
	t_vector v0v2;
	t_vector normal;

	v0v1 = subvect(triangle->v1, triangle->v0);
	v0v2 = subvect(triangle->v2, triangle->v0);
	normal = crossvect(v0v1, v0v2);
	//normalize(&normal); // DO NOT NORMALIZE
	return (normal);
}

float		calcul_dist(t_obj *triangle, t_vector normal)
{
	float d;

	d = prodscal(normal, triangle->v0);
	return (d);
}

int	inside_outside_triangle_test(t_obj *triangle, t_vector normal,t_vector hit_point)
{
	t_vector edge[3];
	t_vector c0;
	t_vector c1;
	t_vector c2;

	edge[0] = subvect(triangle->v1, triangle->v0);
	edge[1] = subvect(triangle->v2, triangle->v1);
	edge[2] = subvect(triangle->v0, triangle->v2);

	c0 = subvect(hit_point, triangle->v0);
	c1 = subvect(hit_point, triangle->v1);
	c2 = subvect(hit_point, triangle->v2);
	return (prodscal(normal, crossvect(edge[0], c0)) > 0.0
		&& prodscal(normal, crossvect(edge[1], c1)) > 0.0
		&& prodscal(normal, crossvect(edge[2], c2)) > 0.0);

}

int	inside_outside_triangle_test2(t_obj *triangle, t_vector normal,t_vector hit_point, double *barycentre)
{
	t_vector edge[3];
	t_vector c0;
	t_vector c1;
	t_vector c2;

	edge[0] = subvect(triangle->v1, triangle->v0);
	edge[1] = subvect(triangle->v2, triangle->v1);
	edge[2] = subvect(triangle->v0, triangle->v2);

	c0 = subvect(hit_point, triangle->v0);
	c1 = subvect(hit_point, triangle->v1);
	c2 = subvect(hit_point, triangle->v2);
	barycentre[0] = prodscal(normal, crossvect(edge[1], c1)) / normevectsquar(normal) ;
	barycentre[1] = prodscal(normal, crossvect(edge[2], c2)) / normevectsquar(normal);
	barycentre[2] = prodscal(normal, crossvect(edge[0], c0)) / normevectsquar(normal);
	return (prodscal(normal, crossvect(edge[0], c0)) > 0.0
		&& barycentre[0] > 0.0
		&& barycentre[1] > 0.0);
}

void	 append_triangle(t_obj *triangle, t_ray ray, t_hit **hit_list)
{
	t_vector	normal;
	double 		t;
	t_hit		*new;
	double		d;
	t_vector	hit_point;
	double		barycentre[3];

	normal = triangle_normal(triangle);
	// are triangle and ray parallel?
	if (fabs(prodscal(normal , ray.dir)) < (double)EPSILON)
		return;
	d = calcul_dist(triangle, normal);
	t = -(prodscal(normal, ray.pos) + d) / prodscal(normal, ray.dir);
	if (t < (double)EPSILON)
		return;
	hit_point = addvect(ray.pos, scalevect(t, ray.dir));
	if((triangle->degrade == 0  && inside_outside_triangle_test(triangle, normal, hit_point))
	|| (triangle->degrade && inside_outside_triangle_test2(triangle, normal, hit_point, &barycentre[0]))
)
	{
		if (!(new = (t_hit*)malloc(sizeof(t_hit))))
			err_exit("Unable to allocate memory\n");
                new->normal = normal;
		normalize(&new->normal);
		new->t = t;
		new->point = hit_point;
		new->displacement = normevectsquar(scalevect(t, ray.dir));
		if (triangle->degrade)
		{
			barycentre[2] = 1.0 - barycentre[0] - barycentre[1];
			triangle->matte = barycentre_color(triangle->glossy, triangle->v1color, triangle->v2color, barycentre);
		}
		new->obj = triangle;
		new->ray_origin = ray.pos;
		new->next = NULL;
		add_point_to_intersection_list(hit_list, new);
	}
}

