/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 01:26:46 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 06:51:25 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void		first_position(t_obj *obj)
{
	t_obj *tmp;

	tmp = obj;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "\tcuboid"))
			rotate_y_obj(tmp, 35.0);
		if (!ft_strcmp(tmp->name, "\tthinring"))
		{
			rotate_x_obj(tmp, 25.0);
			rotate_y_obj(tmp, 25.0);
		}
		else if (!ft_strcmp(tmp->name, "\ttorus"))
		{
			rotate_x_obj(tmp, 220.0);
			rotate_y_obj(tmp, -150.0);
		}
		else if (!ft_strcmp(tmp->name, "\tmobius"))
		{
			rotate_z_obj(tmp, 30.0);
			//rotate_y_obj(tmp, 20.0);
		}
		else if (!ft_strcmp(tmp->name, "\tblock"))
		{
			rotate_y_obj(tmp, 35.0);
		}
		else if (!ft_strcmp(tmp->name, "\tbrick"))
		{
			//rotate_x_obj(tmp, 15.0);
			//rotate_y_obj(tmp, -22.0);
			//rotate_z_obj(tmp, 11.0);
		}
		else if (!ft_strcmp(tmp->name, "\tchessboard"))
		{
			rotate_x_obj(tmp, 28.0);
			rotate_z_obj(tmp, 10.0);
		}

		tmp = tmp->next;
	}
}

void	one_thread_render(void *arg);

int		main(int argc, char *argv[])
{
	t_env *e;
	int checker;

	e = NULL;
	if (argc != 2)
		err_exit("Error.. Usage: ./rt scene_file texture_number(facultatif)\n");
	if (!(e = init_env()))
		err_exit("Unable to allocate memory\n");
	if (!(e->cam = (t_cam*)malloc(sizeof(t_cam))))
		err_exit("Unabale to allaocate camera from main.c");
	checker = scene(argv[1], &e->cam, &e->scene->obj, &e->scene->light, &e->scene->light_obj);
//	init_camera_axes(e->cam);
	if (checker == 0)
		err_exit("Unable to display\n");
	//init_camera_axes(e->cam);
	first_position(e->scene->obj);
	//binary_rotate_y_obj(e->scene->obj, 35); //cuboid
	if(0 == load_all_texture(e))
		destroy_all(&e);
	menu();
	e->is_obj_selected = FALSE;
	all_thread_render(e);
	/*e->main_thread->arg.id = e->num_thread;
	e->main_thread->arg.mlx = e;
	e->main_thread->arg.color = (t_color){0, 0, 0 };;
	e->main_thread->arg.depth = 0;
	one_thread_render((void *)&e->main_thread->arg);*/
	//draw_obj(e);
	//line(e, (t_vector){0, 0, 0}, (t_vector){90,90, 0});
	mlx_mouse_hook(e->win, mouse_hook_func, e);
	mlx_hook(e->win, 17, 18, close_win, e);
	mlx_expose_hook(e->win, expose_hook_func, e);
	mlx_hook(e->win, 2, (1L << 0), cam_hook, e);
	mlx_loop(e->mlx);
	return (0);
}

