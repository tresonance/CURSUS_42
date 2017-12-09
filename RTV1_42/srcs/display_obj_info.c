/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_obj_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 23:38:42 by ibtraore          #+#    #+#             */
/*   Updated: 2017/12/09 15:44:49 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void		display_hit_obj_info(t_env *e)
{
	char *x;
	char *y;
	char *z;
	char *s1;
	char *s2;

	e->itoapos = NULL;
	if (!(e->hit_obj))
		return ;
	x = ft_itoa(e->hit_obj->pos.x);
	y = ft_itoa(e->hit_obj->pos.y);
	z = ft_itoa(e->hit_obj->pos.z);
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

void		display_rot_info(t_env *e)
{
	char *x;
	char *y;
	char *z;
	char *s1;
	char *s2;

	e->itoarot = NULL;
	if (!(e->hit_obj))
		return ;
	x = ft_itoa(e->hit_obj->rot.x);
	y = ft_itoa(e->hit_obj->rot.y);
	z = ft_itoa(e->hit_obj->rot.z);
	s1 = ft_strjoin(x, ",");
	s2 = ft_strjoin(s1, y);
	ft_strdel(&x);
	ft_strdel(&s1);
	s1 = ft_strjoin(s2, ",");
	ft_strdel(&s2);
	s2 = ft_strjoin(s1, z);
	ft_strdel(&s1);
	e->itoarot = ft_strjoin(s2, "]");
	ft_strdel(&s2);
}

void		display_info1(t_env *e, t_obj *obj)
{
	if (e->is_obj_selected)
	{
		e->itoapos = NULL;
		display_hit_obj_info(e);
		mlx_string_put(e->mlx.mlx, e->mlx.win, 340, 415, 0x00FEDC,
				e->hit_obj->name);
		mlx_string_put(e->mlx.mlx, e->mlx.win, 340, 425, 0x00FEDC,
				"--------------");
		mlx_string_put(e->mlx.mlx, e->mlx.win, 340, 435, 0x00FEDC,
				"pos:[");
		mlx_string_put(e->mlx.mlx, e->mlx.win, 392, 435, 0x00FEDC,
				e->itoapos);
	}
}

void		display_info2(t_env *e, t_obj *obj)
{
	int			i;
	char		*name;

	i = -1;
	if (e->hit_obj)
	{
		while (e->hit_obj->name[++i] && '\t' == e->hit_obj->name[i])
			;
		name = &obj->name[i];
		if (0 == ft_strcmp(name, "sphere") || 0 == ft_strcmp(name, "cylinder")
				|| 0 == ft_strcmp(name, "cone"))
		{
			e->itoasize = 0;
			mlx_string_put(e->mlx.mlx, e->mlx.win, 340, 455, 0x00FEDC,
					"size:[");
			e->itoasize = ft_itoa(obj->size);
			mlx_string_put(e->mlx.mlx, e->mlx.win, 400, 455, 0x00FEDC,
					e->itoasize);
			mlx_string_put(e->mlx.mlx, e->mlx.win, 420, 455, 0x00FEDC, "]");
		}
	}
}

int			clicked_obj_info(int x, int y, t_env *e)
{
	double		t;
	t_ray		ray;

	e->hit_obj = NULL;
	current_ray(x, y, e, &ray);
	t = find_closest_t(e->obj, &ray, &e->hit_obj);
	if (t > 0.0001 && t < 8000.0 && e->hit_obj)
	{
		e->hit_obj->current = 0;
		e->is_obj_selected = 1;
		return (1);
	}
	return (0);
}
