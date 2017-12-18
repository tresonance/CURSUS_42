/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_obj_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:48:07 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 16:16:24 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

int	get_degrade(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (ft_strcmp(obj->name, "\ttriangle"))
		return (1);
	if (0 != ft_strncmp("\t\tdegrade(", tab[*i], 10))
		return (err_exit2("bad degrade writing"));
	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	j = 10;
	if (0 == check_param(tab[*i], j, 1))
		return (err_exit2("wrong degrade parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 10.0 || check < 0.0)
		return (err_exit2("wrong degrade parameter value"));
	obj->degrade = (int)check;
	if (')' != tab[*i][j])
		return (err_exit2("wrong degrade end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}



int	get_hide_value(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (ft_strcmp(obj->name, "\tcuboid") && ft_strcmp(obj->name, "\tblock") && ft_strcmp(obj->name, "\tbrick") && ft_strcmp(obj->name, "\tchessboard"))
		return (1);
	if (0 != ft_strncmp("\t\thide(", tab[*i], 7))
		return (err_exit2("bad hide writing"));
	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	j = 7;
	if (0 == check_param(tab[*i], j, 6))
		return (err_exit2("wrong hide parameter number")); 
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("wrong hide value"));
	obj->left = (int)check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("wrong hide value"));
	obj->right = (int)check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("wrong hide value"));
	obj->up = (int)check;

	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("wrong hide value"));
	obj->down = (int)check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("wrong hide value"));
	obj->front = (int)check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("wrong hide value"));
	obj->back = (int)check;

	if (')' != tab[*i][j])
		return (err_exit2("wrong hide end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int		get_cut_info(t_obj *obj, char **tab, int *i)
{
	int j;
	float a;
	int k;

	k = -1;
	if (0 == ft_strncmp(obj->name, "\tlight", 6))
		return (1);
	if (0 != ft_strcmp(obj->name, "\tcylinder") &&  0 != ft_strcmp(obj->name, "\tcone") &&  0 != ft_strcmp(obj->name, "\tplane") && 0 != ft_strcmp(obj->name, "\tsphere"))
		return (1);

	if (0 != ft_strncmp("\t\tcut_info(", tab[*i], 11))
		return (err_exit2("cut_info bad writing"));
		j = 11;
	if (0 == check_param(tab[*i], j, 5))
		return (err_exit2("cut_info bad parameter number"));
		obj->cut_flag = (int)ft_atof(tab[*i], &j);
		a = ft_atof(tab[*i], &j);
		obj->cut_point.x = obj->center.x + a * obj->axe.x;
		obj->cut_point.y = obj->center.y + a * obj->axe.y;
		obj->cut_point.z = obj->center.z + a * obj->axe.z;

		obj->cut_axe.x = ft_atof(tab[*i], &j);
		obj->cut_axe.y = ft_atof(tab[*i], &j);
		obj->cut_axe.z = ft_atof(tab[*i], &j);
		if (')' != tab[*i][j])
			return (err_exit2("bad cut_info end character"));
		if ('\0' != tab[*i][j + 1])
			return (0);
		*i += 1;
	obj->num_cut_plane = k;
	return (1);
}
