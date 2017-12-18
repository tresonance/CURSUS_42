/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_obj_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 23:38:42 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 14:51:26 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		display_hit_obj_position_info(t_env *e)
{
	char *x;
	char *y;
	char *z;
	char *s1;
	char *s2;

	e->itoapos = NULL;
	if (!(e->hit_obj))
		return ;
	x = ft_itoa(e->hit_obj->center.x);
	y = ft_itoa(e->hit_obj->center.y);
	z = ft_itoa(e->hit_obj->center.z);
	s1 = ft_strjoin(x, ",");
	s2 = ft_strjoin(s1, y);
	ft_strdel(&x);
	ft_strdel(&s1);
	s1 = ft_strjoin(s2, ",");
	ft_strdel(&s2);
	s2 = ft_strjoin(s1, z);
	ft_strdel(&s1);
	e->itoapos = ft_strjoin(s2, "]");
	ft_strdel(&s2);
}

int			object_without_defined_axes(t_env *e)
{
	if (ft_strcmp(e->hit_obj->name, "\tcylinder") && ft_strcmp(e->hit_obj->name,
			"\tcone") && ft_strcmp(e->hit_obj->name, "\tplane") && ft_strcmp(
			e->hit_obj->name, "\tthinring") && ft_strcmp(e->hit_obj->name,
				"\ttorus") && ft_strcmp(e->hit_obj->name, "\tmobius"))
		return (FALSE);
	return (TRUE);
}

void		display_hit_obj_axe_info(t_env *e)
{
	char *x;
	char *y;
	char *z;
	char *s1;
	char *s2;

	e->itoaaxe = NULL;
	if (!(e->hit_obj))
		return ;
	if (FALSE == object_without_defined_axes(e))
		return ;
	x = ft_itoa(e->hit_obj->axe.x);
	y = ft_itoa(e->hit_obj->axe.y);
	z = ft_itoa(e->hit_obj->axe.z);
	s1 = ft_strjoin(x, ",");
	s2 = ft_strjoin(s1, y);
	ft_strdel(&x);
	ft_strdel(&s1);
	s1 = ft_strjoin(s2, ",");
	ft_strdel(&s2);
	s2 = ft_strjoin(s1, z);
	ft_strdel(&s1);
	e->itoaaxe = ft_strjoin(s2, "]");
	ft_strdel(&s2);
}

void		display_selected_obj_info1(t_env *e)
{
	if (e->is_obj_selected)
	{
		e->itoapos = NULL;
		display_hit_obj_position_info(e);
		mlx_string_put(e->mlx, e->win, 340, 415, 0x00FEDC,
				e->hit_obj->name);
		mlx_string_put(e->mlx, e->win, 340, 425, 0x00FEDC,
				"--------------");
		mlx_string_put(e->mlx, e->win, 340, 435, 0x00FEDC,
				"pos:[");
		mlx_string_put(e->mlx, e->win, 392, 435, 0x00FEDC,
				e->itoapos);
	}
}

void		display_selected_obj_info2(t_env *e)
{
	int			i;
	char		*name;

	i = -1;
	if (e->hit_obj)
	{
		while (e->hit_obj->name[++i] && '\t' == e->hit_obj->name[i])
			;
		name = &e->hit_obj->name[i];
		if (0 == ft_strcmp(name, "sphere") || 0 == ft_strcmp(name, "cylinder")
				|| 0 == ft_strcmp(name, "cone"))
		{
			e->itoasize = 0;
			mlx_string_put(e->mlx, e->win, 340, 455, 0x00FEDC,
					"size:[");
			e->itoasize = ft_itoa(e->hit_obj->radius);
			mlx_string_put(e->mlx, e->win, 400, 455, 0x00FEDC,
					e->itoasize);
			mlx_string_put(e->mlx, e->win, 420, 455, 0x00FEDC, "]");
		}
	}
}
