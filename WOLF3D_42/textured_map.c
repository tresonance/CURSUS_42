/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 20:46:41 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/24 08:45:34 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int					textured_map(int x, int y)
{
	static int	text_map[22][22] = {
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 7},
	{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
	{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 7},
	{4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7},
	{4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 1},
	{4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 8},
	{4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 1},
	{4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 8},
	{4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 1},
	{4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 1},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 2},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 2},
	{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 2},
	{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 2},
	{4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 2},
	{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3}};

	return (text_map[x][y]);
}

void				init_env2(t_env *e)
{
	t_game		*g;

	load_all_image(e);
	e->endian = 0;
	e->bpp = 24;
	e->posx = 14.5;
	e->posy = 11.5;
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
}

t_textured_img		*ft_load_img_from_file(char *file, t_env *e)
{
	t_textured_img	*image;

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

void				load_all_image(t_env *e)
{
	if (!(e->g = (t_game*)ft_memalloc(sizeof(t_game))))
		err_exit("Unable to allocate memory", 2);
	e->g->texture[0] = ft_load_img_from_file("textures/wood.xpm", e);
	e->g->texture[1] = ft_load_img_from_file("textures/garde.xpm", e);
	e->g->texture[2] = ft_load_img_from_file("textures/haunted.xpm", e);
	e->g->texture[3] = ft_load_img_from_file("textures/caro.xpm", e);
	e->g->texture[8] = ft_load_img_from_file("textures/ciela.xpm", e);
	e->g->texture[4] = ft_load_img_from_file("textures/grass.xpm", e);
	e->g->texture[5] = ft_load_img_from_file("textures/metal.xpm", e);
	e->g->texture[6] = ft_load_img_from_file("textures/stone.xpm", e);
	e->g->texture[7] = ft_load_img_from_file("textures/stone.xpm", e);
	e->g->texture[9] = ft_load_img_from_file("imge_sprites/barrel.xpm", e);
	e->g->texture[10] = ft_load_img_from_file("imge_sprites/pillar.xpm", e);
	e->g->texture[11] = ft_load_img_from_file("imge_sprites/greenlight.xpm", e);
}

void				err_exit(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd(".\n", fd);
	exit(1);
}
