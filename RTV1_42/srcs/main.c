/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 10:14:37 by ibtraore          #+#    #+#             */
/*   Updated: 2017/12/09 15:29:47 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv.h"

void		err_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(".\n", 2);
	exit(1);
}

t_env		*init_env(void)
{
	t_env		*e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (!(e->mlx.mlx = mlx_init()))
		return (NULL);
	if (!(e->mlx.win = mlx_new_window(e->mlx.mlx, WIDTH, HEIGHT, "rtv1"))
	|| !(e->mlx.img = mlx_new_image(e->mlx.mlx, WIDTH, HEIGHT)))
	{
		free(e);
		return (NULL);
	}
	e->mlx.data = mlx_get_data_addr(e->mlx.img, &(e->mlx.bpp),
						&(e->mlx.size_line), &(e->mlx.endian));
	if (!(e->cam = (t_cam*)malloc(sizeof(t_cam))))
	{
		clear_env(&e);
		return (NULL);
	}
	e->hit_obj = NULL;
	e->aa = 1.0;
	e->up = (t_vector){0.0, 1.0, 0.0, 0.0};
	return (e);
}

void		menu(void)
{
	ft_putstr("WELCOME TO RTV1\n");
	ft_putstr("---------------\n\n");
	ft_putstr(">>>Translate objet<<<\n");
	ft_putstr("   ^   \n");
	ft_putstr("<     >\n");
	ft_putstr("   V   \n");
	ft_putstr(">>>Rotate objet<<<\n");
	ft_putstr("1-2, 4-5, 7-8\n\n");
	ft_putstr("Move first light : Q W E D S A\n");
	ft_putstr("Move second light : U I O L J K\n");
	ft_putstr("Anti aliasing : V C B \n");
	ft_putstr("left click : select objet\n");
	ft_putstr("R : stop selecting objet\n");
	ft_putstr("ESC : Quit\n");
}

int			main(int argc, char **argv)
{
	t_env	*e;

	if (argc == 2)
	{
		if (!(e = init_env()))
			err_exit("Unable to allocate");
		e->obj = NULL;
		if (0 == get_scene(&e->obj, e->cam, argv[1]))
		{
			err_exit("SCENE ERROR");
			return (1);
		}
		e->is_obj_selected = 0;
		menu();
		draw_obj(&(*e));
		light_position(e);
		mlx_mouse_hook(e->mlx.win, mouse_hook_func, &(e->mlx));
		mlx_hook(e->mlx.win, 17, 18, close_win, &(e->mlx));
		mlx_expose_hook(e->mlx.win, expose_hook_func, &(e->mlx));
		mlx_hook(e->mlx.win, 2, (1L << 0), key_hook_func, &(e->mlx));
		mlx_loop(e->mlx.mlx);
	}
	else
		err_exit("Usage : ./rtv1 file");
	return (0);
}
