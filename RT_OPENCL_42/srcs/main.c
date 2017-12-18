/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 02:15:09 by thchin            #+#    #+#             */
/*   Updated: 2017/12/15 15:11:39 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			rt_launch2_utils(t_scene *scene)
{
	init_opencl(scene, &scene->cl);
	copy_scene(scene, &scene->cl);
	scene->old_time = 0;
	scene->time = 0;
	scene->gtk.window = NULL;
	scene->gtk.layout = NULL;
}

int				rt_launch2(char *filename, t_scene *scene)
{
	cl_float4	*tmp;
	t_marble	m;
	int			i;

	m.xperiod = 0;
	m.yperiod = 1;
	m.turbpower = 2;
	m.turbsize = 256;
	tmp = create_marble(scene->permtable, scene->bump_data, m);
	scene->bump_image = conv_normalmap(scene->bump_data, tmp);
	free(tmp);
	if (1 == init_scene(filename, scene))
		return (1);
	rt_launch2_utils(scene);
	i = 0;
	while (1)
	{
		if (1 == SDL_PollEvent(&scene->sdl.event))
			key_event(scene, scene->sdl, scene->sdl.event);
		render(scene, scene->sdl, scene->cl);
		update_time(scene);
		window_sdl(scene, i);
		i = i >= 600 ? -15 : i + 15;
	}
	return (0);
}

int				rt_launch(char *filename)
{
	t_scene		*scene;
	SDL_Surface	*img;

	if (NULL == (scene = (t_scene *)malloc(sizeof(t_scene))))
		return (1);
	SDL_Init(SDL_INIT_VIDEO);
	scene->sdl.window = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	scene->sdl.renderer = SDL_CreateRenderer(scene->sdl.window, 0,
					SDL_RENDERER_ACCELERATED);
	scene->sdl.ptr = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	scene->accumtime = 0;
	img = IMG_Load("image/topo_1800.png");
	init_skydome(img, scene);
	SDL_FreeSurface(img);
	scene->sky_surface = IMG_Load("image/star.jpg");
	init_sky(scene->sky_surface, scene);
	init_permtable(scene);
	if (NULL == (scene->bump_data = (t_image *)malloc(sizeof(t_image))))
		return (0);
	scene->bump_data->width = 800;
	scene->bump_data->height = 600;
	return (rt_launch2(filename, scene));
}

int				main(int ac, char **av)
{
	if (ac > 1)
	{
		ft_putstr_fd("Error: Wrong parameter number\n", 2);
		exit(1);
	}
	else
		gtk_launch(ac, av);
	return (0);
}
