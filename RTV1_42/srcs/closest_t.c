/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 06:28:36 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:02:22 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

#define INIT 0
#define ADD 1
#define SUM 2

static void		get_tmp(double *tmp, t_obj *obj, t_ray *ray)
{
	if (0 == ft_strcmp("	sphere", obj->name))
		*tmp = sphere_inter(obj, ray);
	else if (0 == ft_strcmp("	cylinder", obj->name))
		*tmp = cylinder_inter(obj, ray);
	else if (0 == ft_strcmp("	cone", obj->name))
		*tmp = cone_inter(obj, ray);
	else if (0 == ft_strcmp("	plane", obj->name))
		*tmp = plane_inter(obj, ray);
}

double			find_closest_t(t_list *list, t_ray *ray, t_obj **hit_obj)
{
	t_list		*node;
	t_obj		*obj;
	double		t;
	double		tmp;

	t = 8000.0;
	tmp = 8000.0;
	node = list;
	while (node)
	{
		obj = (t_obj *)node->content;
		if (0 != ft_strcmp("	light", obj->name) && 0 == obj->current)
			get_tmp(&tmp, obj, ray);
		if (-1 < tmp && tmp < t)
		{
			t = tmp;
			*hit_obj = obj;
		}
		node = node->next;
	}
	if (-1 < t && t < 8000.0)
		(*hit_obj)->current = 1;
	return (t);
}
