/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <thchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 04:37:06 by thchin            #+#    #+#             */
/*   Updated: 2017/12/15 15:32:49 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_first(t_scene *scene)
{
	scene->mat[0].type = DIFFUSE;
	scene->mat[0].roughness = 1.0f;
	scene->mat[0].coef = 1.0f;
	scene->text[0].id = 0;
	scene->text[0].pos = 0;
	scene->text[0].xoffset = 0;
	scene->text[0].yoffset = 0;
	scene->text[0].startoffset.s[0] = 0.0f;
	scene->text[0].startoffset.s[1] = 0.0f;
	scene->text[0].startoffset.s[2] = 0.0f;
	scene->text[0].startoffset.s[3] = 1.0f;
	scene->bump[0].id = 0;
	scene->bump[0].pos = 0;
	scene->bump[0].xoffset = 0;
	scene->bump[0].yoffset = 0;
	scene->bump[0].startoffset.s[0] = 0.0f;
	scene->bump[0].startoffset.s[1] = 0.0f;
	scene->bump[0].startoffset.s[2] = 0.0f;
	scene->bump[0].startoffset.s[3] = 1.0f;
}

void	init_prev_scene(char *file, t_scene *scene)
{
	count_obj(file, scene);
	if (NULL == (scene->mat = (t_material *)malloc(scene->info->nb_mat *
		sizeof(t_material))))
		return ;
	if (NULL == (scene->text = (t_text *)malloc(scene->info->nb_text *
		sizeof(t_text))))
		return ;
	if (NULL == (scene->prim = (t_prim *)malloc(scene->info->nb_prim *
		sizeof(t_prim))))
		return ;
	if (NULL == (scene->bump = (t_text *)malloc(scene->info->nb_bump *
		sizeof(t_text))))
		return ;
	if (NULL == (scene->light = (t_light *)malloc(scene->info->nb_light *
		sizeof(t_light))))
		return ;
	init_zero(scene);
	init_first(scene);
	parse_prim(file, scene);
	parse_mat(file, scene);
	parse_text(file, scene);
	parse_bump(file, scene);
	parse_light(file, scene);
}

int		init_scene(char *file, t_scene *scene)
{
	cl_float4	up;

	if (NULL == (scene->cam = (t_cam *)malloc(sizeof(t_cam))))
		return (1);
	parse_cam(file, scene);
	up.s[0] = 0.0f;
	up.s[1] = 1.0f;
	up.s[2] = 0.0f;
	up.s[3] = 0.0f;
	scene->cam->normal = normalize(subvect(scene->cam->dir, scene->cam->pos));
	scene->cam->right = normalize(crossvect(scene->cam->normal, up));
	scene->cam->up = normalize(crossvect(scene->cam->right,
	scene->cam->normal));
	if (NULL == (scene->info = (t_info *)malloc(sizeof(t_info))))
		return (1);
	scene->info->nb_prim = 0;
	scene->info->nb_light = 0;
	scene->info->nb_text = 1;
	scene->info->nb_bump = 1;
	scene->info->nb_mat = 1;
	scene->info->aa = 1;
	init_prev_scene(file, scene);
	return (0);
}
