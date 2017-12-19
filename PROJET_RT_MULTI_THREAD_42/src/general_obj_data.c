/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_obj_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:48:07 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 15:55:56 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int	is_light_object(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	if (0 != ft_strncmp("\t\tis_light(", tab[*i], 11))
		return (err_exit2("is_light"));
	j = 11;
	if (0 == check_param(tab[*i], j, 1))
		return (err_exit2("\"is_light\" parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check < 0.0)
		return (err_exit2("is_light wrong parameter"));
	obj->is_light_obj = (int)check;
	if (')' != tab[*i][j])
		return (err_exit2("is_light bad end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	csg_operator(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	if (0 != ft_strncmp("\t\tcsg_operator(", tab[*i], 15))
		return (err_exit2("bad csg operator"));
	j = 15;
	if (0 == check_param(tab[*i], j, 1))
		return (err_exit2("wrong \"csg_operator\" parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 3.0f)
		return (err_exit2("is_light wrong parameter"));
	obj->csg_operator = (int)check;
	if (')' != tab[*i][j])
		return (err_exit2(" bad csg_operator end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}


int	get_matte_color(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (0 != ft_strncmp("\t\tcolor_matte(", tab[*i], 14))
		return (err_exit2("color_matte"));
	j = 14;
	if (0 == check_param(tab[*i], j, 3))
		return (err_exit2("matte color wrong parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("color_matte wrong value"));
	obj->matte.r = check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("color_matte wrong value"));
	obj->matte.g = check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("color_matte wrong value"));
	obj->matte.b = check;
	if (')' != tab[*i][j])
		return (err_exit2("color_matte bad end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_matte_colorv1(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (ft_strcmp(obj->name, "\ttriangle"))
		return (1);
	if (obj->degrade == 0)
		return (1);
	if (0 != ft_strncmp("\t\tcolor_matte(", tab[*i], 14))
		return (err_exit2("triangle color_matte"));
	j = 14;
	if (0 == check_param(tab[*i], j, 3))
		return (err_exit2("color_matte wrong parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("color_matte wrong parameter value"));
	obj->v1color.r = check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("color_matte wrong parameter value"));
	obj->v1color.g = check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("color_matte wrong parameter value"));
	obj->v1color.b = check;
	if (')' != tab[*i][j] || '\0' != tab[*i][j + 1])
		return (err_exit2("color_matte bad end character"));
	*i += 1;
	return (1);
}

int	get_matte_colorv2(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (ft_strcmp(obj->name, "\ttriangle"))
		return (1);
	if (obj->degrade == 0)
		return (1);
	if (0 != ft_strncmp("\t\tcolor_matte(", tab[*i], 14))
		return (err_exit2("triangle color_matte 2"));
	j = 14;
	if (0 == check_param(tab[*i], j, 3))
		return (err_exit2("color_matte 2 wrong parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("color_matte 2 bad value"));
	obj->v2color.r = check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("color_matte 2 bad value"));
	obj->v2color.g = check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("color_matte 2 bad value"));
	obj->v2color.b = check;
	if (')' != tab[*i][j] || '\0' != tab[*i][j + 1])
		return (err_exit2("color_matte 2 bad value"));
	*i += 1;
	return (1);
}
