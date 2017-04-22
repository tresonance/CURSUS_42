/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 03:35:54 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/22 02:53:51 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

int				check_param(char *str, int i, int max)
{
	int	words;

	words = 0;
	if (str[i] != '\0' && 0 == ft_iswhitespace(str[i]))
		words += 1;
	i += 1;
	while (str[i] != '\0' && str[i] != ')')
	{
		if (1 == ft_iswhitespace(str[i - 1]) && 0 == ft_iswhitespace(str[i]))
			words += 1;
		i += 1;
	}
	if (words != max)
		return (0);
	return (1);
}

static void		parser_cam1(t_cam **cam, char ***tab, int *i)
{
	(*cam)->pos.x = ft_atof((*tab)[2], &(*i));
	(*cam)->pos.y = ft_atof((*tab)[2], &(*i));
	(*cam)->pos.z = ft_atof((*tab)[2], &(*i));
	(*cam)->pos.w = 1.0;
}

int				parser_cam(t_cam *cam, char **tab)
{
	int	i;

	if (0 != ft_strcmp("camera", tab[0]) && 0 != ft_strcmp("{", tab[1]))
		return (0);
	if (0 != ft_strncmp("	pos(", tab[2], 5))
		return (0);
	i = 5;
	if (0 == check_param(tab[2], i, 3))
		return (0);
	parser_cam1(&cam, &tab, &i);
	if (0 != ft_strcmp(")", &tab[2][i]))
		return (0);
	if (0 != ft_strncmp("	dir(", tab[3], 5))
		return (0);
	i = 5;
	if (0 == check_param(tab[3], i, 3))
		return (0);
	cam->dir.x = ft_atof(tab[3], &i);
	cam->dir.y = ft_atof(tab[3], &i);
	cam->dir.z = ft_atof(tab[3], &i);
	cam->dir.w = 1.0;
	if (0 != ft_strcmp(")", &tab[3][i]) && 0 != ft_strcmp("}", tab[4]))
		return (0);
	return (1);
}
