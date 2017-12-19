/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 02:15:09 by thchin            #+#    #+#             */
/*   Updated: 2017/12/15 15:11:41 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_opencl(t_scene *scene, t_opencl *cl)
{
	clGetPlatformIDs(1, &cl->platform_id, NULL);
	clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, 1, &cl->device_id,
					NULL);
	cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL, NULL);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device_id,
										CL_QUEUE_PROFILING_ENABLE, NULL);
	cl->program = build_source(cl->context, cl->device_id,
								"cl_function/raytrace.cl");
	cl->renderkernel = build_renderkernel(cl->program, cl->context, scene,
										&scene->cl);
	clReleaseProgram(cl->program);
}

void			print_time(t_scene *e, cl_event event, int i)
{
	cl_ulong	time_start;
	cl_ulong	time_end;

	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
							sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
							sizeof(time_end), &time_end, NULL);
	e->total_time = time_end - time_start;
	e->total_time_1 = e->total_time;
	e->total_time_2 = e->total_time;
	if (i == 1)
		e->total_time_1 /= 1000000.0f;
	else if (i == 2)
		e->total_time_2 /= 1000000.0f;
}

void			render(t_scene *e, t_sdl sdl, t_opencl cl)
{
	size_t		global_work_size;
	size_t		local_work_size;
	cl_ulong	size;
	cl_event	event;

	global_work_size = WIDTH * HEIGHT;
	clGetDeviceInfo(cl.device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE,
					sizeof(cl_ulong), &size, NULL);
	local_work_size = size;
	if (global_work_size % local_work_size != 0)
		global_work_size = (global_work_size / local_work_size + 1) *
							local_work_size;
	clEnqueueNDRangeKernel(cl.command_queue, cl.renderkernel, 1, NULL,
						&global_work_size, &local_work_size, 0, NULL, &event);
	clWaitForEvents(1, &event);
	print_time(e, event, 1);
	clEnqueueReadBuffer(cl.command_queue, cl.buffer, CL_TRUE, 0,
			WIDTH * HEIGHT * 4 * sizeof(Uint8), sdl.ptr->pixels, 0, NULL,
		&event);
	clWaitForEvents(1, &event);
	clFinish(cl.command_queue);
	print_time(e, event, 2);
	flip(sdl, sdl.ptr);
}

void			clear_scene1(t_scene *scene)
{
	if (scene)
	{
		(scene)->cam ? free((scene)->cam) : 0;
		(scene)->prim ? free((scene)->prim) : 0;
		(scene)->light ? free((scene)->light) : 0;
		(scene)->info ? free((scene)->info) : 0;
		(scene)->image ? free((scene)->image) : 0;
		(scene)->data ? free((scene)->data) : 0;
		(scene)->sky_data ? free((scene)->sky_data) : 0;
		(scene)->mat ? free((scene)->mat) : 0;
		(scene)->text ? free((scene)->text) : 0;
		(scene)->bump ? free((scene)->bump) : 0;
		(scene)->bump_image ? free((scene)->bump_image) : 0;
		(scene)->bump_data ? free((scene)->bump_data) : 0;
		free(scene);
		SDL_Quit();
	}
}

void			clear_scene(t_scene *scene)
{
	clReleaseKernel(scene->cl.renderkernel);
	clReleaseMemObject(scene->cl.buffer);
	clReleaseMemObject(scene->cl.cam);
	clReleaseMemObject(scene->cl.prim);
	clReleaseMemObject(scene->cl.material);
	clReleaseMemObject(scene->cl.text);
	clReleaseMemObject(scene->cl.bump);
	clReleaseMemObject(scene->cl.light);
	clReleaseMemObject(scene->cl.info);
	clReleaseMemObject(scene->cl.image);
	clReleaseMemObject(scene->cl.data);
	clReleaseMemObject(scene->cl.sky);
	clReleaseMemObject(scene->cl.sky_data);
	clReleaseMemObject(scene->cl.bump_image);
	clReleaseMemObject(scene->cl.bump_data);
	clReleaseCommandQueue(scene->cl.command_queue);
	clReleaseContext(scene->cl.context);
	SDL_DestroyRenderer(scene->sdl.renderer);
	SDL_DestroyWindow(scene->sdl.window);
	SDL_FreeSurface(scene->sdl.ptr);
	SDL_FreeSurface(scene->sky_surface);
	clear_scene1(scene);
	exit(0);
}
