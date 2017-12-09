/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 02:09:31 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/05 12:53:15 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void	copy_cam(t_cam *dst, t_cam src)
{
	dst->pos.x = src.pos.x;
	dst->pos.y = src.pos.y;
	dst->pos.z = src.pos.z;
	dst->pos.w = src.pos.w;
	dst->dir.x = src.dir.x;
	dst->dir.y = src.dir.y;
	dst->dir.z = src.dir.z;
	dst->dir.w = src.dir.w;
}

void	copy_obj(t_obj *dst, t_obj src)
{
	dst->name = ft_strdup(src.name);
	dst->pos.x = src.pos.x;
	dst->pos.y = src.pos.y;
	dst->pos.z = src.pos.z;
	dst->pos.w = src.pos.w;
	dst->color.r = src.color.r;
	dst->color.g = src.color.g;
	dst->color.b = src.color.b;
	dst->rot.x = src.rot.x;
	dst->rot.y = src.rot.y;
	dst->rot.z = src.rot.z;
	dst->rot.w = src.rot.w;
	dst->size = src.size;
	dst->ambient = src.ambient;
	dst->diffuse = src.diffuse;
	dst->specular = src.specular;
	dst->current = src.current;
}

int		copy_list(t_list **dst, t_list *src)
{
	t_list	*new;
	t_list	*tmp;
	t_obj	*obj;
	t_obj	*tmp_obj;

	*dst = NULL;
	tmp = src;
	while (tmp != NULL)
	{
		obj = (t_obj *)tmp->content;
		if (NULL == (tmp_obj = (t_obj *)malloc(sizeof(t_obj))))
			return (-1);
		copy_obj(tmp_obj, *obj);
		if (NULL == (new = (ft_lstnew((void *)tmp_obj, sizeof(t_obj)))))
			return (-1);
		lst_add_back(dst, new);
		tmp = tmp->next;
	}
	return (0);
}

void	copy_up(t_vector *dst, t_vector src)
{
	dst->x = src.x;
	dst->y = src.y;
	dst->z = src.z;
	dst->w = src.w;
}
