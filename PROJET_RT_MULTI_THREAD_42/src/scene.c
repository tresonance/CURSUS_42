/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:56:46 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/15 23:56:53 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

void		add_obj_to_scene(t_obj **obj, t_obj *new)
{
	t_obj *tmp;

	if (!*obj)
		*obj = new;
	else
	{
		tmp = *obj;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
	
void		add_light_source_to_scene(t_light **light, t_obj *light_point)
{
	t_light *tmp;
	t_light *new;

	if (!(new = (t_light*)malloc(sizeof(t_light))))
		err_exit("Unable to allocate new from \"scene.c\".");
	new->pos = light_point->center;
	new->color = light_point->matte;
	new->parallel = light_point->parallel;
	new->next = NULL;

	if (!*light)
		*light = new;
	else
	{
		tmp = *light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		add_light_obj_to_scene(t_light_obj **light, t_obj *obj)
{
	t_light_obj *tmp;
	t_light_obj *new;

	if (!(new = (t_light_obj*)malloc(sizeof(t_light_obj))))
		err_exit("Unable to allocate new from \"scene.c\".");
	new->obj = obj;
	new->next = NULL;
	if (!*light)
		*light = new;
	else
	{
		tmp = *light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
