/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 07:40:44 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:03:09 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int	get_ambient(t_obj *obj, char **tab, int *i)
{
	int	j;

	if (0 != ft_strncmp("		ambient(", tab[*i], 10))
		return (0);
	j = 10;
	if (0 == check_param(tab[*i], j, 1))
		return (0);
	obj->ambient = ft_atof(tab[*i], &j);
	if (obj->ambient < 0 || obj->ambient >= 1)
		return (0);
	if (')' != tab[*i][j])
		return (0);
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_diffuse(t_obj *obj, char **tab, int *i)
{
	int	j;

	if (0 != ft_strncmp("		diffuse(", tab[*i], 10))
		return (0);
	j = 10;
	if (0 == check_param(tab[*i], j, 1))
		return (0);
	obj->diffuse = ft_atof(tab[*i], &j);
	if (obj->diffuse < 0 || obj->diffuse >= 1)
		return (0);
	if (')' != tab[*i][j])
		return (0);
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_specular(t_obj *obj, char **tab, int *i)
{
	int	j;

	if (0 != ft_strncmp("		specular(", tab[*i], 11))
		return (0);
	j = 11;
	if (0 == check_param(tab[*i], j, 1))
		return (0);
	obj->specular = ft_atof(tab[*i], &j);
	if (obj->specular < 0 || obj->specular >= 1)
		return (0);
	if (')' != tab[*i][j])
		return (0);
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_light_info(t_obj *obj, char **tab, int *i)
{
	if (0 == get_ambient(obj, tab, i))
		return (0);
	if (0 == get_diffuse(obj, tab, i))
		return (0);
	if (0 == get_specular(obj, tab, i))
		return (0);
	return (1);
}
