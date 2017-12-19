/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brel-baz <brel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 09:49:11 by brel-baz          #+#    #+#             */
/*   Updated: 2017/12/15 13:02:56 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_mat(t_scene *scene)
{
	int i;

	i = 1;
	while (i < scene->info->nb_mat)
	{
		scene->mat[i].type = DIFFUSE;
		scene->mat[i].roughness = 1.0f;
		scene->mat[i].coef = 1.0f;
		i++;
	}
}

void	init_text(t_scene *scene)
{
	int i;

	i = 1;
	while (i < scene->info->nb_text)
	{
		scene->text[i].id = 0;
		scene->text[i].pos = 0;
		scene->text[i].xoffset = 0;
		scene->text[i].yoffset = 0;
		scene->text[i].startoffset.s[0] = 0.0f;
		scene->text[i].startoffset.s[1] = 0.0f;
		scene->text[i].startoffset.s[2] = 0.0f;
		scene->text[i].startoffset.s[3] = 1.0f;
		i++;
	}
}

void	init_bump(t_scene *scene)
{
	int i;

	i = 1;
	while (i < scene->info->nb_bump)
	{
		scene->bump[i].id = 0;
		scene->bump[i].pos = 0;
		scene->bump[i].xoffset = 0;
		scene->bump[i].yoffset = 0;
		scene->bump[i].startoffset.s[0] = 0.0f;
		scene->bump[i].startoffset.s[1] = 0.0f;
		scene->bump[i].startoffset.s[2] = 0.0f;
		scene->bump[i].startoffset.s[3] = 1.0f;
		i++;
	}
}

void	init_zero(t_scene *scene)
{
	init_mat(scene);
	init_bump(scene);
	init_text(scene);
	init_prim(scene);
}
