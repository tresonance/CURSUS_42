/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 22:25:36 by thchin            #+#    #+#             */
/*   Updated: 2017/12/14 23:15:56 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	flip(t_sdl sdl, SDL_Surface *ptr)
{
	SDL_Texture	*text;

	text = SDL_CreateTextureFromSurface(sdl.renderer, ptr);
	SDL_RenderCopy(sdl.renderer, text, NULL, NULL);
	SDL_RenderPresent(sdl.renderer);
	SDL_DestroyTexture(text);
}

void	show_perlinmap(cl_float4 *image, t_image *info, t_sdl sdl)
{
	SDL_Surface	*ptr;
	int			x;
	int			y;
	Uint8		*p;

	ptr = SDL_CreateRGBSurface(0, info->width, info->height, 32, 0, 0, 0, 0);
	x = 0;
	y = 0;
	while (y < info->height)
	{
		p = (Uint8 *)ptr->pixels + y * ptr->pitch + x
			* ptr->format->BytesPerPixel;
		p[2] = image[y * info->width + x].s[0] * 255;
		p[1] = image[y * info->width + x].s[1] * 255;
		p[0] = image[y * info->width + x].s[2] * 255;
		p[3] = 255;
		x += 1;
		if (x >= info->width)
		{
			y += 1;
			x = 0;
		}
	}
	flip(sdl, ptr);
	SDL_FreeSurface(ptr);
}

void	show_normalmap(cl_float4 *image, t_image *info, t_sdl sdl)
{
	SDL_Surface	*ptr;
	int			x;
	int			y;
	Uint8		*p;

	ptr = SDL_CreateRGBSurface(0, info->width, info->height, 32, 0, 0, 0, 0);
	x = 0;
	y = 0;
	while (y < info->height)
	{
		p = (Uint8 *)ptr->pixels + y * ptr->pitch + x
			* ptr->format->BytesPerPixel;
		p[2] = (image[y * info->width + x].s[0] + 1) * 0.5f * 255;
		p[1] = (image[y * info->width + x].s[1] + 1) * 0.5f * 255;
		p[0] = (image[y * info->width + x].s[2] + 1) * 0.5f * 255;
		p[3] = 255;
		x += 1;
		if (x >= info->width)
		{
			y += 1;
			x = 0;
		}
	}
	flip(sdl, ptr);
	SDL_FreeSurface(ptr);
}
