/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:58:45 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 06:44:22 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"


static t_texture	*load_texture(char *file, t_env *e)
{
	t_texture *tex;

	if (!(tex = (t_texture*)ft_memalloc(sizeof(t_texture))))
		return (NULL);
	if(!(tex->image = mlx_xpm_file_to_image(e->mlx, file, &tex->width, &tex->height)))
	{
		ft_memdel((void**)&tex);
		return (NULL);
	}
	tex->imgptr = mlx_get_data_addr(tex->image, &tex->bpp, &tex->sl, &tex->endian);
	return (tex);
}

int	load_all_texture(t_env *e)
{
	int i;
	const char *texture[] = {"rt_textures/iblack_white.xpm", "rt_textures/iblue_yellow.xpm", "rt_textures/igreen_white.xpm", "rt_textures/imarbe_multi_color.xpm", "rt_textures/imarbe_uni_color.xpm", "rt_textures/iworld_map.xpm", "rt_textures/iworld_map2.xpm", NULL};

	e->total_texture = 0;
	while (texture[e->total_texture] != NULL)
		e->total_texture++;
	if (!(e->texture_arr = (t_texture**)malloc((e->total_texture) * sizeof(t_texture*))))
		return (0);
	i = -1;
	while (++i < e->total_texture)
	{
		if(!(e->texture_arr[i] = load_texture((char*)texture[i], e)))
			return (0);	
	}
	return (1);
}

int		shape_index(t_hit *inter)
{
	int i;
	const char *shape[] = {"\tsphere", "\tplane", "\tcylinder", "\ttriangle", "\tcuboid", "\tblock", "\ttbrick", "\tchessboard", "\tthinring" , "\ttorus", "\tmobius", "\tcone", NULL};
	i = -1;
	while (shape[++i] != NULL)
	{
		if (ft_strcmp(inter->obj->name, shape[i]) == 0)
			return (i);
	}
	ft_putstr("cannot find index from \"texture.c\".\n");
	return (-1);
}

t_color		get_texture_color(t_hit *inter, t_env *e)
{
	ptr_f func[13] = {&get_sphere_texture_color, &get_plane_texture_color, &get_cylinder_texture_color, &get_triangle_texture_color, &get_cuboid_texture_color, &get_block_texture_color, &get_brick_texture_color, &get_chessboard_texture_color , &get_thinring_texture_color, &get_torus_texture_color, &get_mobius_texture_color, &get_cone_texture_color, NULL};
	int index;

	if (inter->obj->tag == 8)
		return (get_procedural_texture_color(inter));
	if (inter->obj->tag == 9)
		return (get_procedural_texture_color2(inter));
	if (inter->obj->tag == 10)
		return (perlin_color(inter, e));
	if (inter->obj->tag < 1 || inter->obj->tag > e->total_texture)
	{
		destroy_all(&e);
		err_exit("wrong ta number.\n");
	}
	index = shape_index(inter);
	return ((index != -1) ? (func[index])(inter, e):(t_color){ 0.0, 0.0, 0.0} );
}

t_color		texture_rgb(int u, int v, t_texture *tex)
{
	t_color color;
	float index;
	
	color = (t_color){0.0, 0.0, 0.0};
	if (u >= 0.0 && v >= 0.0 && u < tex->width && v < tex->height)
	{
		index = (u *  tex->bpp/8) + (v  * tex->sl);
		color.r = tex->imgptr[(int)index] / 255.0;
		color.g = tex->imgptr[1 + (int)index] / 255.0;
		color.b = tex->imgptr[2 + (int)index] / 255.0;
	}
	return (color);
}

t_color		texture_color(t_env *e, t_hit *inter, float u, float v)
{
	t_texture *tex;
	t_color col;

	if (inter->obj->tag < 1 || inter->obj->tag > e->total_texture)
	{
		destroy_all(&e);
		err_exit("wrong ta number.\n");
	}
	tex = e->texture_arr[inter->obj->tag - 1];
	// fetch a bilinearly filtered textel
	float fu = (u + 1000.5f) * tex->width;
	float fv = (v + 1000.0f) * tex->height;

	int u1 = ((int)fu) % tex->width;
	int v1 = ((int)fv) % tex->height;

	int u2 = (u1 + 1) % tex->width;
	int v2 = (v1 + 1) % tex->height;

	//calculate fractional part u v
	float fracu = fu - floorf( fu );
	float fracv = fv - floorf( fv );

	//calculate weight factor
	float w1 = (1.0 - fracu) * (1.0 - fracv);
	float w2 = fracu * (1.0 - fracv);
	float w3 = (1.0 - fracu) * fracv;
	float w4 = fracu * fracv;

	//fetch for textels
	t_color c1 = texture_rgb(u1, v1, tex);
	t_color c2 = texture_rgb(u2, v1, tex);
	t_color c3 = texture_rgb(u1, v2, tex);
	t_color c4 = texture_rgb(u2, v2, tex);

	col.r = ((w1 * c1.r) + (w2 * c2.r) + (w3 * c3.r) + (w4 * c4.r));
	col.g = ((w1 * c1.g) + (w2 * c2.g) + (w3 * c3.g) + (w4 * c4.g));
	col.b = ((w1 * c1.b) + (w2 * c2.b) + (w3 * c3.b) + (w4 * c4.b));
	return (col);
}


