/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_obj_data2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:56:17 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 16:08:29 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int	get_triangle_position(t_obj **obj, char **tab, int *i, int *j)
{
	if (0 == check_param(tab[*i], *j, 9))
		return (err_exit2("triangle position"));
	(*obj)->v0.x = ft_atof(tab[*i], j);
	(*obj)->v0.y = ft_atof(tab[*i], j);
	(*obj)->v0.z = ft_atof(tab[*i], j);
	(*obj)->v1.x = ft_atof(tab[*i], j);
	(*obj)->v1.y = ft_atof(tab[*i], j);
	(*obj)->v1.z = ft_atof(tab[*i], j);
	(*obj)->v2.x = ft_atof(tab[*i], j);
	(*obj)->v2.y = ft_atof(tab[*i], j);
	(*obj)->v2.z = ft_atof(tab[*i], j);
	return (1);
}

void		init_obj_base(t_obj **obj)
{
	(*obj)->base.rdir = (t_vector){1.0, 0.0, 0.0};
	(*obj)->base.sdir = (t_vector){0.0, 1.0, 0.0};
	(*obj)->base.tdir = (t_vector){0.0, 0.0, 1.0};
	(*obj)->enclosed = (int)TRUE;
}

int			get_position(t_obj *obj, char **tab, int *i)
{
	int		j;

	if (0 != ft_strncmp("\t\tpos(", tab[*i], 6))
		return (err_exit2("position bad writing"));
	j = 6;
	if (0 == ft_strcmp(obj->name, "\ttriangle"))
	{
		if (0 == get_triangle_position(&obj, tab, i, &j))
			return (err_exit2("wrong position"));
	}
	else
	{
		if (0 == ft_strcmp(obj->name, "\tlight"))
		{
			if (0 == check_param(tab[*i], j, 4))
				return (err_exit2("wrong light dir parameter number"));
		obj->center = (t_vector){ft_atof(tab[*i], &j), ft_atof(tab[*i], &j),
			ft_atof(tab[*i], &j)};
		obj->parallel = (int)ft_atof(tab[*i], &j);
		}
		else
		{
			if (0 == check_param(tab[*i], j, 3))
				return (err_exit2("wrong light pos parameter number"));
		obj->center = (t_vector){ft_atof(tab[*i], &j), ft_atof(tab[*i], &j),
			ft_atof(tab[*i], &j)};
		obj->parallel = (int)ft_atof(tab[*i], &j);
		}
	}
	if (')' != tab[*i][j] || '\0' != tab[*i][j + 1])
		return (err_exit2("bad position end character"));
	if (ft_strcmp(obj->name, "\tlight"))
		init_obj_base(&obj);
	*i += 1;
	return (1);
}

int			get_glossy_color(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (0 != ft_strncmp("\t\tcolor_glossy(", tab[*i], 15))
		return (err_exit2("wrong color_glossy"));
	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	j = 15;
	if (0 == check_param(tab[*i], j, 3))
		return (err_exit2("wrong glossy parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("glossy wrong value"));
	obj->glossy.r = check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("glossy wrong value"));
	obj->glossy.g = check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("glossy wrong value"));
	obj->glossy.b = check;
	if (')' != tab[*i][j])
		return (err_exit2("glossy bad end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int			get_indice(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (0 != ft_strncmp("\t\tindice(", tab[*i], 9))
		return (err_exit2("wrong indice writing"));
	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	j = 9;
	if (0 == check_param(tab[*i], j, 1))
		return (err_exit2("wrong indice parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > ((double)INDICE_MAXIMUM)
			|| check < ((double)INDICE_MINIMUM))
		return (err_exit2("indice out of range"));
	obj->refractive_index = check;
	if (')' != tab[*i][j])
		return (err_exit2("wrong indice end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}
