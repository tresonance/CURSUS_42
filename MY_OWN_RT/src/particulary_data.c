/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particulary_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:53:02 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/15 23:53:10 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

int	get_size(t_obj *obj, char **tab, int *i)
{
	int	j;

	if (0 != ft_strncmp("\t\tsize(", tab[*i], 7))
		return (err_exit2("wrong size parameter number"));
	j = 7;
	/*if (!ft_strcmp(obj->name,"\tsphere"))
	{
		if(0 == check_param(tab[*i], j, 1))
			return (0);
		obj->radius = ft_atof(tab[*i], &j);
	}*/
	/*if (!ft_strcmp(obj->name,"\tbox"))
	{
		if(0 == check_param(tab[*i], j, 1))
			return (err_exit2("wrong size parameter number"));
		obj->a = ft_atof(tab[*i], &j);
	}*/
	if (!ft_strcmp(obj->name,"\tcuboid") || !ft_strcmp(obj->name,"\tblock") || !ft_strcmp(obj->name, "\tbrick") || !ft_strcmp(obj->name, "\tchessboard") || !ft_strcmp(obj->name,"\tthinring") || !ft_strcmp(obj->name,"\tbox") )
	{
		if(0 == check_param(tab[*i], j, 3))
			return (err_exit2("wrong size parameter number"));
		obj->a = ft_atof(tab[*i], &j);
		obj->b = ft_atof(tab[*i], &j);
		obj->c = ft_atof(tab[*i], &j);
	}
	else if (!ft_strcmp(obj->name,"\ttorus") || !ft_strcmp(obj->name,"\tmobius"))
	{
		if(0 == check_param(tab[*i], j, 2))
			return (err_exit2("wrong size parameter number"));
		obj->a = ft_atof(tab[*i], &j);
		obj->b = ft_atof(tab[*i], &j);
	}
	else if (!ft_strcmp(obj->name,"\tcylinder") || !ft_strcmp(obj->name,"\tsphere") || !ft_strcmp(obj->name,"\tcone"))
	{
		if(0 == check_param(tab[*i], j, 1))
			return (err_exit2("wrong size parameter number"));
			obj->radius = ft_atof(tab[*i], &j);
			//obj->zdisk = ft_atof(tab[*i], &j);
	}
	if (')' != tab[*i][j])
		return (err_exit2("wrong size end parameter"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_axe(t_obj *obj, char **tab, int *i)
{
	int	j;

	if (0 != ft_strncmp("\t\taxe(", tab[*i], 6))
		return (0);
	j = 6;
	if (0 == check_param(tab[*i], j, 3))
		return (err_exit2("wrong axe parameter number"));
	obj->axe.x = ft_atof(tab[*i], &j);
	obj->axe.y = ft_atof(tab[*i], &j);
	obj->axe.z = ft_atof(tab[*i], &j);
	if (')' != tab[*i][j])
		return (err_exit2("wrong axe end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}
