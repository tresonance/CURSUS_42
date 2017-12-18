/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prim_co.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <brel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 02:18:30 by brel-baz          #+#    #+#             */
/*   Updated: 2017/12/15 12:58:14 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define NB_TEXT scene->info->nb_text
#define NB_MAT scene->info->nb_mat

void	parse_prim_co1(char *str, char **str2, t_scene *scene, int j)
{
	int i;

	if (ft_strcmp("prim_pos", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[j].pos.s[i] = ft_atof(str2[i]);
	}
	if (ft_strcmp("prim_pos1", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[j].pos1.s[i] = ft_atof(str2[i]);
	}
	if (ft_strcmp("prim_pos2", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[j].pos2.s[i] = ft_atof(str2[i]);
	}
}

void	parse_prim_co2(char *str, char **str2, t_scene *scene, int j)
{
	int i;

	if (ft_strcmp("prim_color", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[j].color.s[i] = ft_atof(str2[i]);
	}
	if (ft_strcmp("prim_rot", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[j].rot.s[i] = ft_atof(str2[i]);
	}
	if (ft_strcmp("prim_type", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[j].type = convert_define(str2[i]);
	}
}

void	parse_prim_co3(char *str, char **str2, t_scene *scene, int *j)
{
	int i;

	if (ft_strcmp("prim_text", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[*j].text = ft_atof(str2[i]);
		if (scene->prim[*j].text < 0 || scene->prim[*j].text > NB_TEXT)
		{
			ft_putstr("Error: text not exist\n");
			exit(1);
		}
	}
	if (ft_strcmp("prim_mat", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[*j].mat = ft_atof(str2[i]);
		if (scene->prim[*j].mat < 0 || scene->prim[*j].mat > NB_MAT)
		{
			ft_putstr("Error: mat not exist\n");
			exit(1);
		}
	}
}

void	parse_prim_co4(char *str, char **str2, t_scene *scene, int *j)
{
	int i;

	if (ft_strcmp("prim_size", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[*j].size = ft_atof(str2[i]);
	}
	if (ft_strcmp("prim_bump", str) == 0)
	{
		i = -1;
		while (str2[++i])
			scene->prim[*j].bump = ft_atof(str2[i]);
		if (scene->prim[*j].bump < 0 ||
		scene->prim[*j].bump > scene->info->nb_bump)
		{
			ft_putstr("Error: bump not exist\n");
			exit(1);
		}
	}
	if (ft_strcmp("prim_end", str) == 0)
		*j += 1;
}

void	parse_prim_co(char *str, char **str2, t_scene *scene, int *i)
{
	parse_prim_co1(str, str2, scene, *i);
	parse_prim_co2(str, str2, scene, *i);
	parse_prim_co3(str, str2, scene, i);
	parse_prim_co4(str, str2, scene, i);
}
