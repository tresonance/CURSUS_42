/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_obj_data3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:09:01 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 16:09:55 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int	get_matte_factor(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (0 != ft_strncmp("\t\tmatte_factor(", tab[*i], 15))
		return (err_exit2("wrong matte_factor writing"));
	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	j = 15;
	if (0 == check_param(tab[*i], j, 1))
		return (err_exit2("wrong matte_factor parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("wrong matte_factor parameter value"));
	obj->matte_factor = check;
	if (')' != tab[*i][j])
		return (err_exit2("bad matte_factor end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_glossy_factor(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (0 != ft_strncmp("\t\tglossy_factor(", tab[*i], 16))
		return (err_exit2("glossy_factor bad writing"));
	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	j = 16;
	if (0 == check_param(tab[*i], j, 1))
		return (err_exit2("wrong glossy_factor parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("bad glossy_factor value"));
	obj->glossy_factor = check;
	if (')' != tab[*i][j])
		return (err_exit2("bad glossy_factor end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_specular_factor(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (0 != ft_strncmp("\t\tspecular_factor(", tab[*i], 18))
		return (err_exit2("specular_factor bad writing"));
	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	j = 18;
	if (0 == check_param(tab[*i], j, 1))
		return (err_exit2("specular_factor wrong parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 1.0 || check < 0.0)
		return (err_exit2("specular_factor bad value"));
	obj->specular_factor = check;
	if (')' != tab[*i][j])
		return (err_exit2("bad specular_factor end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_tag(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (0 != ft_strncmp("\t\ttag(", tab[*i], 6))
		return (err_exit2("bad tag writing"));
	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	j = 6;
	if (0 == check_param(tab[*i], j, 1))
		return (err_exit2("wrong tag parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 10.0 || check < 0.0)
		return (err_exit2("bad tag value"));
	obj->tag = (int)check;
	if (')' != tab[*i][j])
		return (err_exit2("bad tag end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_type(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (0 != ft_strncmp("\t\ttype(", tab[*i], 7))
		return (err_exit2("bad type writing"));
	if (!ft_strcmp(obj->name, "\tlight"))
		return (1);
	j = 7;
	if (0 == check_param(tab[*i], j, 2))
		return (err_exit2("bad tag parameter number"));
	if (0 > (check = ft_atof(tab[*i], &j)) || check < 0.0)
		return (0);
	obj->type[0] = (int)check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check < 0.0)
		return (err_exit2("wrong type value"));
	obj->type[1] = (int)check;
	if (')' != tab[*i][j])
		return (err_exit2("wrong type end character"));
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}
