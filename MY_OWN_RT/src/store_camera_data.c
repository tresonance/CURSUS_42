/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_camera_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:58:06 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 03:07:28 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

int				check_param(char *str, int i, int max)
{
	int	words;

	words = 0;
	if (str[i] != '\0' && 0 == ft_iswhitespace(str[i]))
		words += 1;
	i += 1;
	while (str[i] != '\0' && str[i] != ')')
	{
		if (i - 1 >= 0 && 1 == ft_iswhitespace(str[i - 1]) &&
			0 == ft_iswhitespace(str[i]))
			words += 1;
		i += 1;
	}
	if (words != max)
		return (0);
	return (1);
}

static void		parser_cam1(t_cam **cam, char ***tab, int *i)
{
	if (*cam == NULL)
		err_exit("Wrong camera adress\n");
	(*cam)->pos.x = ft_atof((*tab)[2], &(*i));
	(*cam)->pos.y = ft_atof((*tab)[2], &(*i));
	(*cam)->pos.z = ft_atof((*tab)[2], &(*i));
}

int				parser_cam(t_cam *cam, char **tab)
{
	int	i;

	if ((0 != ft_strcmp("camera", tab[0]) && 0 != ft_strcmp("{", tab[1])))
		return (0);
	if (0 != ft_strncmp("\tpos(", tab[2], 5))
		return (0);
	if (0 != ft_strncmp("\tlookat(", tab[3], 8))
		return (0);
	i = 5;
	if (0 == check_param(tab[2], i, 3))
		return (0);
	parser_cam1(&cam, &tab, &i);
	if (0 != ft_strcmp(")", &tab[2][i]))
		return (0);
	//if (0 != ft_strncmp("lookat(", tab[3], 7))
	//	return (0);
	i = 8;
	if (0 == check_param(tab[3], i, 3))
		return (0);
	cam->lookat.x = ft_atof(tab[3], &i);
	cam->lookat.y = ft_atof(tab[3], &i);
	cam->lookat.z = ft_atof(tab[3], &i);
	if (0 != ft_strcmp(")", &tab[3][i]) && 0 != ft_strcmp("}", tab[4]))
		return (0);
	return (1);
}
