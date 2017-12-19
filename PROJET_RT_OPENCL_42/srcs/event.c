/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 04:55:45 by thchin            #+#    #+#             */
/*   Updated: 2017/12/15 15:32:57 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define CAM_DIR scene->cam->dir
#define CAM_POS scene->cam->pos
#define CAM_NORMAL scene->cam->normal
#define CAM_RIGHT scene->cam->right
#define CAM_UP scene->cam->up
#define SPEED 1
#define RSPEED 1

void	translate(SDL_Event event, t_scene *scene, cl_float4 *v)
{
	if (KEY == SDLK_w)
		*v = addvect(scalevect(CAM_UP, SPEED), *v);
	if (KEY == SDLK_s)
		*v = subvect(*v, scalevect(CAM_UP, SPEED));
	if (KEY == SDLK_a)
		*v = addvect(scalevect(CAM_RIGHT, SPEED), *v);
	if (KEY == SDLK_d)
		*v = subvect(*v, scalevect(CAM_RIGHT, SPEED));
	if (KEY == SDLK_UP)
		*v = addvect(scalevect(CAM_NORMAL, SPEED), *v);
	if (KEY == SDLK_DOWN)
		*v = subvect(*v, scalevect(CAM_NORMAL, SPEED));
}

void	rotate(SDL_Event event, t_scene *scene, cl_float4 *v)
{
	cl_float4	q;
	float		angle;

	angle = ((float)RSPEED * M_PI / 180) / 2;
	if (KEY == SDLK_KP_8)
		q = scalevect(CAM_RIGHT, sin(angle));
	if (KEY == SDLK_KP_2)
		q = scalevect(CAM_RIGHT, sin(angle * -1.0f));
	if (KEY == SDLK_KP_4)
		q = scalevect(CAM_UP, sin(angle * -1.0f));
	if (KEY == SDLK_KP_6)
		q = scalevect(CAM_UP, sin(angle));
	if (KEY == SDLK_KP_7)
		q = scalevect(CAM_NORMAL, sin(angle));
	if (KEY == SDLK_KP_9)
		q = scalevect(CAM_NORMAL, sin(angle * -1.0f));
	q.s[3] = cos(angle);
	if (KEY != SDLK_KP_9 && KEY != SDLK_KP_7)
		*v = subvect(*v, CAM_POS);
	*v = hamilton_product(q, *v);
	*v = hamilton_product(*v, conjugate(q));
	if (KEY != SDLK_KP_9 && KEY != SDLK_KP_7)
		*v = addvect(*v, CAM_POS);
}

void	key_event1(t_scene *scene, t_sdl sdl, SDL_Event event)
{
	if (KEY == SDLK_KP_8 || KEY == SDLK_KP_2 || KEY == SDLK_KP_4 ||
			KEY == SDLK_KP_6 || KEY == SDLK_KP_7 || KEY == SDLK_KP_9)
	{
		if (KEY != SDLK_KP_7 && KEY != SDLK_KP_9)
		{
			rotate(sdl.event, scene, &CAM_DIR);
			CAM_NORMAL = normalize(subvect(CAM_DIR, CAM_POS));
			CAM_RIGHT = normalize(crossvect(CAM_NORMAL, CAM_UP));
			CAM_UP = normalize(crossvect(CAM_RIGHT, CAM_NORMAL));
		}
		else
		{
			rotate(sdl.event, scene, &CAM_RIGHT);
			CAM_UP = normalize(crossvect(CAM_RIGHT, CAM_NORMAL));
		}
		clEnqueueWriteBuffer(scene->cl.command_queue, scene->cl.cam,
				CL_TRUE, 0, sizeof(t_cam), scene->cam, 0, NULL, NULL);
	}
}

void	key_event(t_scene *scene, t_sdl sdl, SDL_Event event)
{
	if (event.type == SDL_QUIT)
		clear_scene(scene);
	if (event.type == SDL_KEYDOWN)
	{
		if (KEY == SDLK_ESCAPE)
			clear_scene(scene);
		if (KEY == SDLK_p)
			SDL_SaveBMP(sdl.ptr, "screenshot.bmp");
		else if (KEY == SDLK_w || KEY == SDLK_s || KEY == SDLK_a ||
				KEY == SDLK_d || KEY == SDLK_UP || KEY == SDLK_DOWN)
		{
			translate(sdl.event, scene, &CAM_DIR);
			translate(sdl.event, scene, &CAM_POS);
			clEnqueueWriteBuffer(scene->cl.command_queue, scene->cl.cam,
					CL_TRUE, 0, sizeof(t_cam), scene->cam, 0, NULL, NULL);
		}
		else
			key_event1(scene, sdl, event);
	}
}
