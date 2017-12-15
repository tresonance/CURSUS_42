/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_co.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <brel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 02:34:15 by brel-baz          #+#    #+#             */
/*   Updated: 2017/12/15 12:38:32 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_cam_co(char *str, char **str2, t_cam **cam)
{
	int i;

	if (ft_strcmp("cam_pos", str) == 0)
	{
		i = -1;
		while (str2[++i])
			(*cam)->pos.s[i] = ft_atof(str2[i]);
	}
	if (ft_strcmp("cam_dir", str) == 0)
	{
		i = -1;
		while (str2[++i])
			(*cam)->dir.s[i] = ft_atof(str2[i]);
	}
}

void	parse_mat_co(char *str, char **str2, t_scene *scene, int *j)
{
	int i;

	if (ft_strcmp("mat_type", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->mat[*j].type = convert_define2(str2[i]);
	}
	if (ft_strcmp("mat_roughness", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->mat[*j].roughness = ft_atof(str2[i]);
	}
	if (ft_strcmp("mat_coef", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->mat[*j].coef = ft_atof(str2[i]);
	}
	if (ft_strcmp("mat_end", str) == 0)
		*j += 1;
}

void	parse_light_co1(char *str, char **str2, t_light *light, int *j)
{
	int i;

	if (ft_strcmp("light_type", str) == 0)
	{
		i = -1;
		while (str2[++i])
			light[*j].type = convert_define2(str2[i]);
	}
	if (ft_strcmp("light_pos", str) == 0)
	{
		i = -1;
		while (str2[++i])
			light[*j].pos.s[i] = ft_atof(str2[i]);
	}
	if (ft_strcmp("light_color", str) == 0)
	{
		i = -1;
		while (str2[++i])
			light[*j].color.s[i] = ft_atof(str2[i]);
	}
}

void	parse_light_co2(char *str, char **str2, t_light *light, int *j)
{
	int i;

	if (ft_strcmp("light_intensity", str) == 0)
	{
		i = -1;
		while (str2[++i])
			light[*j].intensity = ft_atof(str2[i]);
	}
	if (ft_strcmp("light_end", str) == 0)
		*j += 1;
}

void	parse_light_co(char *str, char **str2, t_light *light, int *j)
{
	parse_light_co1(str, str2, light, j);
	parse_light_co2(str, str2, light, j);
}
