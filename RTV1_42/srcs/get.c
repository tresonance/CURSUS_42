/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 07:33:11 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:03:04 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int	get_col(t_obj *obj, char **tab, int *i)
{
	int		j;
	double	check;

	if (0 != ft_strncmp("		col(", tab[*i], 6))
		return (0);
	j = 6;
	if (0 == check_param(tab[*i], j, 3))
		return (0);
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 255)
		return (0);
	obj->color.r = (uint8_t)check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 255)
		return (0);
	obj->color.g = (uint8_t)check;
	if (0 > (check = ft_atof(tab[*i], &j)) || check > 255)
		return (0);
	obj->color.b = (uint8_t)check;
	if (')' != tab[*i][j])
		return (0);
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_pos(t_obj *obj, char **tab, int *i)
{
	int	j;

	if (0 != ft_strncmp("		pos(", tab[*i], 6))
		return (0);
	j = 6;
	if (0 == check_param(tab[*i], j, 3))
		return (0);
	obj->pos.x = ft_atof(tab[*i], &j);
	obj->pos.y = ft_atof(tab[*i], &j);
	obj->pos.z = ft_atof(tab[*i], &j);
	obj->pos.w = 1.0;
	if (')' != tab[*i][j])
		return (0);
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_size(t_obj *obj, char **tab, int *i)
{
	int	j;

	if (0 != ft_strncmp("		size(", tab[*i], 7))
		return (0);
	j = 7;
	if (0 == check_param(tab[*i], j, 1))
		return (0);
	obj->size = ft_atof(tab[*i], &j);
	if (')' != tab[*i][j])
		return (0);
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}

int	get_rot(t_obj *obj, char **tab, int *i)
{
	int	j;

	if (0 != ft_strncmp("		rot(", tab[*i], 6))
		return (0);
	j = 6;
	if (0 == check_param(tab[*i], j, 3))
		return (0);
	obj->rot.x = ft_atof(tab[*i], &j);
	obj->rot.y = ft_atof(tab[*i], &j);
	obj->rot.z = ft_atof(tab[*i], &j);
	obj->rot.w = 0.0;
	if (')' != tab[*i][j])
		return (0);
	if ('\0' != tab[*i][j + 1])
		return (0);
	*i += 1;
	return (1);
}
