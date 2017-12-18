/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 04:41:29 by thchin            #+#    #+#             */
/*   Updated: 2017/12/14 23:08:15 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	copy_scene1(t_scene *scene, t_opencl *cl)
{
	clEnqueueWriteBuffer(cl->command_queue, cl->cam, CL_TRUE, 0, sizeof(t_cam),
						scene->cam, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->prim, CL_TRUE, 0,
						scene->info->nb_prim * sizeof(t_prim),
						scene->prim, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->material, CL_TRUE, 0,
						scene->info->nb_mat * sizeof(t_material),
						scene->mat, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->text, CL_TRUE, 0,
						scene->info->nb_text * sizeof(t_text),
						scene->text, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->bump, CL_TRUE, 0,
						scene->info->nb_bump * sizeof(t_text),
						scene->bump, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->light, CL_TRUE, 0,
						scene->info->nb_light * sizeof(t_light),
						scene->light, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->info, CL_TRUE, 0,
						sizeof(t_info), scene->info, 0, NULL, NULL);
}

void	copy_scene(t_scene *scene, t_opencl *cl)
{
	copy_scene1(scene, cl);
	clEnqueueWriteBuffer(cl->command_queue, cl->image, CL_TRUE, 0,
				scene->data->width * scene->data->height * sizeof(cl_float4),
				scene->image, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->data, CL_TRUE, 0,
						sizeof(t_image), scene->data, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->sky, CL_TRUE, 0,
		scene->sky_data->width * scene->sky_data->height * 3 * sizeof(Uint8),
		scene->sky, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->sky_data, CL_TRUE, 0,
						sizeof(t_image), scene->sky_data, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->bump_image, CL_TRUE, 0,
		scene->bump_data->width * scene->bump_data->height * sizeof(cl_float4),
		scene->bump_image, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->command_queue, cl->bump_data, CL_TRUE, 0,
			sizeof(t_image), scene->bump_data, 0, NULL, NULL);
}
