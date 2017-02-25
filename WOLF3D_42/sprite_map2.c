/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 08:31:30 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/25 07:08:01 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void				init_env3(t_env *e)
{
	t_game *g;

	load_all_image3(e);
	e->endian = 0;
	e->bpp = 24;
	e->posx = 17.5;
	e->posy = 5.5;
	e->dirx = -1;
	e->diry = 0;
	e->planex = 0;
	e->planey = 0.66;
	e->hit = 0;
	e->wallheight = 64;
	e->wallwidth = 64;
	e->perpwalldist = 0;
	e->rotspeed = M_PI / (double)48;
	e->translspeed = 0.1;
	init_sprite(e);
}

t_textured_img		*ft_load_img_from_file2(char *file, t_env *e)
{
	t_textured_img *image;

	if (!(image = (t_textured_img*)ft_memalloc(sizeof(t_textured_img))))
		return (NULL);
	if (!(image->img = mlx_xpm_file_to_image(e->mlx, file, &image->width,
		&image->height)))
	{
		ft_memdel((void **)&image);
		return (NULL);
	}
	image->imgptr = mlx_get_data_addr(image->img, &image->bpp,
	&image->size_line, &image->endian);
	return (image);
}

void				load_all_image3(t_env *e)
{
	if (!(e->g = (t_game*)ft_memalloc(sizeof(t_game))))
		err_exit("Unable to allocate memory", 2);
	e->g->texture[0] = ft_load_img_from_file2("textures/wood.xpm", e);
	e->g->texture[1] = ft_load_img_from_file2("textures/garde.xpm", e);
	e->g->texture[2] = ft_load_img_from_file2("textures/haunted.xpm", e);
	e->g->texture[3] = ft_load_img_from_file2("textures/caro.xpm", e);
	e->g->texture[8] = ft_load_img_from_file2("textures/ciela.xpm", e);
	e->g->texture[4] = ft_load_img_from_file2("textures/grass.xpm", e);
	e->g->texture[5] = ft_load_img_from_file2("textures/metal.xpm", e);
	e->g->texture[6] = ft_load_img_from_file2("textures/stone.xpm", e);
	e->g->texture[7] = ft_load_img_from_file2("textures/stone.xpm", e);
	e->g->texture[11] = ft_load_img_from_file2("image_sprites/officier.xpm", e);
	e->g->texture[9] = ft_load_img_from_file2("image_sprites/pillar.xpm", e);
	e->g->texture[10] = ft_load_img_from_file2("image_sprites/police.xpm", e);
}
