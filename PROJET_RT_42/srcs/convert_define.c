/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_define.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <brel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 01:59:01 by brel-baz          #+#    #+#             */
/*   Updated: 2017/12/15 13:02:48 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		convert_define(char *str)
{
	if (ft_strcmp("SPHERE", str) == 0)
		return (SPHERE);
	if (ft_strcmp("PLANE", str) == 0)
		return (PLANE);
	if (ft_strcmp("CONE", str) == 0)
		return (CONE);
	if (ft_strcmp("CYLINDER", str) == 0)
		return (CYLINDER);
	if (ft_strcmp("BOX", str) == 0)
		return (BOX);
	if (ft_strcmp("SKY", str) == 0)
		return (SKY);
	if (ft_strcmp("TRIANGLE", str) == 0)
		return (TRIANGLE);
	if (ft_strcmp("PARABOLOID", str) == 0)
		return (PARABOLOID);
	if (ft_strcmp("TORE", str) == 0)
		return (TORE);
	return (42);
}

int		convert_define2(char *str)
{
	if (ft_strcmp("POINT", str) == 0)
		return (POINT);
	if (ft_strcmp("PARRALEL", str) == 0)
		return (PARRALEL);
	if (ft_strcmp("DIFFUSE", str) == 0)
		return (DIFFUSE);
	if (ft_strcmp("REFLECTIVE", str) == 0)
		return (REFLECTIVE);
	if (ft_strcmp("REFRACTIVE", str) == 0)
		return (REFRACTIVE);
	if (ft_strcmp("TRANSPARANT", str) == 0)
		return (TRANSPARANT);
	return (42);
}

void	init_prim1(t_scene *scene)
{
	int i;

	i = 0;
	while (i < scene->info->nb_prim)
	{
		scene->prim[i].type = SPHERE;
		scene->prim[i].pos.s[0] = 0;
		scene->prim[i].pos.s[1] = 0;
		scene->prim[i].pos.s[2] = 0;
		scene->prim[i].pos.s[3] = 1;
		scene->prim[i].pos1.s[0] = 0;
		scene->prim[i].pos1.s[1] = 0;
		scene->prim[i].pos1.s[2] = 0;
		scene->prim[i].pos1.s[3] = 1;
		scene->prim[i].pos2.s[0] = 0;
		scene->prim[i].pos2.s[1] = 0;
		scene->prim[i].pos2.s[2] = 0;
		scene->prim[i].pos2.s[3] = 1;
		i++;
	}
}

void	init_prim2(t_scene *scene)
{
	int i;

	i = 0;
	while (i < scene->info->nb_prim)
	{
		scene->prim[i].color.s[0] = 1;
		scene->prim[i].color.s[1] = 1;
		scene->prim[i].color.s[2] = 1;
		scene->prim[i].color.s[3] = 1;
		scene->prim[i].rot.s[0] = 0;
		scene->prim[i].rot.s[1] = 0;
		scene->prim[i].rot.s[2] = 0;
		scene->prim[i].rot.s[3] = 0;
		scene->prim[i].size = 0;
		scene->prim[i].mat = 0;
		scene->prim[i].text = 0;
		scene->prim[i].bump = 0;
		i++;
	}
}

void	init_prim(t_scene *scene)
{
	init_prim1(scene);
	init_prim2(scene);
}
