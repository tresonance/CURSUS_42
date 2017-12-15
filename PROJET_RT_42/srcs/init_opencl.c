/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 02:17:25 by thchin            #+#    #+#             */
/*   Updated: 2017/12/15 15:13:54 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_log(cl_program program, cl_device_id device_id)
{
	size_t	log_size;
	char	*log;

	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL,
							&log_size);
	if (NULL == (log = (char *)malloc(log_size)))
		return ;
	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
							log_size, log, NULL);
	free(log);
}

cl_program	build_source(cl_context context, cl_device_id device_id, char *name)
{
	cl_int		result;
	FILE		*fp;
	char		*str;
	cl_program	program;

	fp = fopen(name, "rb");
	if (!fp)
	{
		ft_putendl("fail to load kernel");
		exit(1);
	}
	str = (char *)malloc(MAXSOURCESIZE);
	ft_memset(str, 0, MAXSOURCESIZE);
	fread(str, 1, MAXSOURCESIZE, fp);
	fclose(fp);
	program = clCreateProgramWithSource(context, 1, (const char **)&str, NULL,
										&result);
	result = clBuildProgram(program, 1, &device_id, "-I ./cl_function", NULL,
							NULL);
	if (result == CL_BUILD_PROGRAM_FAILURE)
		print_log(program, device_id);
	free(str);
	str = NULL;
	return (program);
}

void		create_text(cl_context context, t_scene *scene, t_opencl *cl)
{
	cl->image = clCreateBuffer(context, CL_MEM_READ_WRITE,
		scene->data->width * scene->data->height * sizeof(cl_float4),
		NULL, NULL);
	cl->data = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(t_image), NULL,
		NULL);
	cl->sky = clCreateBuffer(context, CL_MEM_READ_WRITE,
		scene->sky_data->width * scene->sky_data->height * 3 * sizeof(Uint8),
		NULL, NULL);
	cl->sky_data = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(t_image),
		NULL, NULL);
	cl->bump_image = clCreateBuffer(context, CL_MEM_READ_WRITE,
		scene->bump_data->width * scene->bump_data->height * sizeof(cl_float4),
		NULL, NULL);
	cl->bump_data = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(t_image),
		NULL, NULL);
}

void		create_buffer(cl_context context, t_scene *scene, t_opencl *cl)
{
	cl->buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
		WIDTH * HEIGHT * 4 * sizeof(Uint8), NULL, NULL);
	cl->cam = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(t_cam),
		NULL, NULL);
	cl->prim = clCreateBuffer(context, CL_MEM_READ_WRITE,
		scene->info->nb_prim * sizeof(t_prim), NULL, NULL);
	cl->material = clCreateBuffer(context, CL_MEM_READ_WRITE,
		scene->info->nb_mat * sizeof(t_material), NULL, NULL);
	cl->text = clCreateBuffer(context, CL_MEM_READ_WRITE,
		scene->info->nb_text * sizeof(t_text), NULL, NULL);
	cl->bump = clCreateBuffer(context, CL_MEM_READ_WRITE,
		scene->info->nb_bump * sizeof(t_text), NULL, NULL);
	cl->light = clCreateBuffer(context, CL_MEM_READ_WRITE,
		scene->info->nb_light * sizeof(t_light), NULL, NULL);
	cl->info = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(t_info),
		NULL, NULL);
}

cl_kernel	build_renderkernel(cl_program program, cl_context context,
								t_scene *scene, t_opencl *cl)
{
	cl_kernel	kernel;

	kernel = clCreateKernel(program, "renderer", NULL);
	create_buffer(context, scene, cl);
	create_text(context, scene, cl);
	clSetKernelArg(kernel, 0, sizeof(cl->buffer), (void *)&cl->buffer);
	clSetKernelArg(kernel, 1, sizeof(cl->cam), (void *)&cl->cam);
	clSetKernelArg(kernel, 2, sizeof(cl->prim), (void *)&cl->prim);
	clSetKernelArg(kernel, 3, sizeof(cl->material), (void *)&cl->material);
	clSetKernelArg(kernel, 4, sizeof(cl->text), (void *)&cl->text);
	clSetKernelArg(kernel, 5, sizeof(cl->bump), (void *)&cl->bump);
	clSetKernelArg(kernel, 6, sizeof(cl->light), (void *)&cl->light);
	clSetKernelArg(kernel, 7, sizeof(cl->info), (void *)&cl->info);
	clSetKernelArg(kernel, 8, sizeof(cl->image), (void *)&cl->image);
	clSetKernelArg(kernel, 9, sizeof(cl->data), (void *)&cl->data);
	clSetKernelArg(kernel, 10, sizeof(cl->sky), (void *)&cl->sky);
	clSetKernelArg(kernel, 11, sizeof(cl->sky_data), (void *)&cl->sky_data);
	clSetKernelArg(kernel, 12, sizeof(cl->bump_image), (void *)&cl->bump_image);
	clSetKernelArg(kernel, 13, sizeof(cl->bump_data), (void *)&cl->bump_data);
	return (kernel);
}
