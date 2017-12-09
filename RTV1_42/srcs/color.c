/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 22:46:36 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/05 12:52:27 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

double	shadow(t_list *list, t_obj *light, t_hit hit)
{
	double		t;
	t_vector	l;
	t_vector	ln;
	t_obj		*hit_obj;
	t_ray		ray;

	hit_obj = NULL;
	l = subvect(&hit.point, &light->pos);
	ln.x = l.x;
	ln.y = l.y;
	ln.z = l.z;
	normalize(&l);
	ray.pos = hit.point;
	ray.dir = l;
	t = find_closest_t(list, &ray, &hit_obj);
	if (hit_obj != NULL)
		hit_obj->current = 0;
	if (0.0001 < t && t < sqrtf(prodscal(&ln, &ln)))
		return (t);
	return (-1);
}

double	get_spec(t_vector l, t_vector v, t_hit hit)
{
	t_vector	halfway;
	double		specular;

	halfway = addvect(&l, &v);
	normalize(&halfway);
	specular = prodscal(&hit.normal, &halfway);
	specular = specular > 0.0001 ? specular : 0.0;
	specular = pow(specular, 100);
	return (specular);
}

t_color	set_color(t_obj *light, t_obj *obj, double specul, double cos_teta)
{
	t_color col;

	col.r = ((obj->color.r / 255.0) * obj->ambient +
			(light->color.r / 255.0) * obj->diffuse * cos_teta +
			(light->color.r / 255.0) * specul * obj->specular) * 255;
	col.g = ((obj->color.g / 255.0) * obj->ambient +
			(light->color.g / 255.0) * obj->diffuse * cos_teta +
			(light->color.g / 255.0) * specul * obj->specular) * 255;
	col.b = ((obj->color.b / 255.0) * obj->ambient +
			(light->color.b / 255.0) * obj->diffuse * cos_teta +
			(light->color.b / 255.0) * specul * obj->specular) * 255;
	return (col);
}

t_color	get_hit_color(t_list *list, t_obj *light, t_obj *obj, t_hit hit)
{
	t_color		col;
	t_vector	v;
	t_vector	l;
	double		cos_teta;
	double		specular;

	l = subvect(&hit.point, &light->pos);
	v = subvect(&hit.point, &hit.ray_origin->pos);
	normalize(&v);
	normalize(&l);
	if (-1 < shadow(list, light, hit))
	{
		col.r = obj->color.r * obj->ambient;
		col.g = obj->color.g * obj->ambient;
		col.b = obj->color.b * obj->ambient;
		return (col);
	}
	cos_teta = ft_clamp(prodscal(&hit.normal, &l), 0, 1);
	specular = get_spec(l, v, hit);
	col = set_color(light, obj, specular, cos_teta);
	return (col);
}

t_color	lighting(t_list *list, t_obj **obj, t_ray ray, double t)
{
	t_list	*tmp;
	t_color	col;
	t_hit	hit;
	t_color	tmp_col;

	tmp = list;
	hit.t = t;
	col.r = 0;
	col.g = 0;
	col.b = 0;
	get_hit_point_info(&hit, *obj, &ray);
	while (tmp)
	{
		if (ft_strcmp(((t_obj*)tmp->content)->name, "	light") == 0)
		{
			tmp_col = get_hit_color(list, (t_obj*)tmp->content, *obj, hit);
			col.r = (col.r + tmp_col.r) > 255 ? 255 : col.r + tmp_col.r;
			col.g = (col.g + tmp_col.g) > 255 ? 255 : col.g + tmp_col.g;
			col.b = (col.b + tmp_col.b) > 255 ? 255 : col.b + tmp_col.b;
		}
		tmp = tmp->next;
	}
	return (col);
}
