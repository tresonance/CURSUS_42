/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:47:29 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 14:30:49 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		destroy_all(t_env **e)
{
	int		i;

	if (*e)
	{
		destroy_texture_array(*e);
		destroy_scene(&((*e)->scene));
		(*e)->win ? free((*e)->win) : 0;
		free((*e)->cam);
		(void)((*e)->mlx);
		ft_strdel(&(*e)->itoacampos);
		ft_strdel(&(*e)->itoacamdir);
		ft_strdel(&(*e)->itoaaxe);
		ft_strdel(&(*e)->itoasize);
		i = -1;
		while (++i < (*e)->num_thread * (*e)->num_thread)
			ft_memdel((void **)&(*e)->thread_array[i]);
		free(*e);
	}
}

void		clear_env(t_env **e)
{
	if (*e)
	{
		destroy_texture_array(*e);
		destroy_scene(&((*e)->scene));
		(*e)->img ? mlx_destroy_image((*e)->mlx, (*e)->img) : 0;
		(*e)->win ? free((*e)->win) : 0;
		(*e)->mlx ? free((*e)->mlx) : 0;
		(*e)->cam ? free((*e)->cam) : 0;
		free(*e);
		e = NULL;
	}
	exit(0);
}

void		destroy_scene(t_scene **scene)
{
	t_obj	*obj;
	t_light *light;

	if (*scene)
	{
		while ((*scene)->obj)
		{
			obj = (*scene)->obj;
			(*scene)->obj = obj->next;
			ft_strdel(&(obj->name));
			free(obj);
		}
		while ((*scene)->light)
		{
			light = (*scene)->light;
			(*scene)->light = light->next;
			free(light);
		}
		free(*scene);
	}
}

void		destroy_intersection_list(t_hit **hit_list)
{
	t_hit	*tmp;

	if (!hit_list || !*hit_list)
		return;
	while (*hit_list)
	{
		tmp = *hit_list;
		free(*hit_list);
		*hit_list = tmp->next;
		//free(tmp);
	}
	*hit_list = NULL;
}

void		destroy_texture_array(t_env *e)
{
	int		i;

	if (e->texture_arr)
	{
		i = -1;
		while (++i < e->total_texture)
		{
			ft_memdel((void**)&e->texture_arr[i]->image);
			ft_memdel((void**)&e->texture_arr[i]);
		}
		ft_memdel((void**)e->texture_arr);
	}
}
