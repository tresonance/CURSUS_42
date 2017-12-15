/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_skydome.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <thchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 04:44:34 by thchin            #+#    #+#             */
/*   Updated: 2017/12/15 13:35:13 by brel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_image	*init_data_image(SDL_Surface *img)
{
	t_image		*data;

	if (NULL == (data = (t_image *)malloc(sizeof(t_image))))
		return (NULL);
	data->width = img->w;
	data->height = img->h;
	return (data);
}

int		init_skydome(SDL_Surface *img, t_scene *scene)
{
	Uint8	*pixel;
	int		x;
	int		y;

	if (NULL == (scene->data = init_data_image(img)))
		return (1);
	if (NULL == (scene->image = (cl_float4 *)malloc(sizeof(cl_float4) *
	img->w * img->h)))
		return (1);
	x = -1;
	while (++x < img->w)
	{
		y = -1;
		while (++y < img->h)
		{
			pixel = (Uint8 *)img->pixels + y * img->pitch + x *
			img->format->BytesPerPixel;
			scene->image[y * img->w + x].s[0] = (float)pixel[0] / 255;
			scene->image[y * img->w + x].s[1] = (float)pixel[1] / 255;
			scene->image[y * img->w + x].s[2] = (float)pixel[2] / 255;
			scene->image[y * img->w + x].s[3] = 1.0f;
		}
	}
	return (0);
}

int		init_sky(SDL_Surface *img, t_scene *scene)
{
	if (NULL == (scene->sky_data = (t_image *)malloc(sizeof(t_image))))
		return (1);
	scene->sky_data->width = img->w;
	scene->sky_data->height = img->h;
	scene->sky = img->pixels;
	return (0);
}
