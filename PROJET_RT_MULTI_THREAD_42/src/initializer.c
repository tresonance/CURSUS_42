/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:48:29 by ibtraore          #+#    #+#             */
/*   Updated: 2017/08/16 05:45:04 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/rt.h"

void		init_camera_axes(t_cam *cam)
{
		if (cam == NULL)
			err_exit("Wrong camera adress\n");
		cam->dir = subvect(cam->lookat, cam->pos);
        	normalize(&cam->dir);
        	//cam->right = crossvect(cam->dir, ((t_vector){0.0, 1.0 ,0.0}));
        	cam->right = crossvect(((t_vector){0.0, 1.0 ,0.0}), cam->dir);
        	normalize(&cam->right);
		//cam->up = crossvect(cam->right, cam->dir);
		cam->up = crossvect(cam->dir, cam->right);
        	normalize(&cam->up);
}

t_scene		*initialize_scene(void)
{
	t_scene *scene;

	if (!(scene= (t_scene*)malloc(sizeof(t_scene))))
		return (NULL);
	scene->obj = NULL;
	scene->light = NULL;
	scene->light_obj = NULL;
	scene->ambient_refractive_index = (double)REFRACTION_VACUUM;
	scene->background = (t_color){0, 0, 0};
	return (scene);
}


t_env 		*init_env(void)
{
	t_env *e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	//e->cam = NULL;
	if(!(e->mlx = mlx_init()))
	{
		free(e);
		return (NULL);
	}
	if(!(e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "RT"))
			|| !(e->img = mlx_new_image(e->mlx, WIDTH + 100, HEIGHT + 100))
			|| !(e->scene = initialize_scene())/* || !(e->cam = (t_cam*)malloc(sizeof(t_cam)))*/)
	{
		e->win ? free(e->win) : 0;
		e->img ? free(e->img) : 0;
		e->scene ? free(e->scene) : 0;
		//e->cam ? free(e->cam) : 0;
		//(void)e->mlx;
		free(e->mlx);
		free(e);
		return (NULL);

	}
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->sl), &(e->endian));
	e->hit_list = NULL;
	e->texture_arr = NULL;
	e->up = (t_vector){0.0, 1.0, 0.0};
	//e->p = 0;
	e->aa = 1;
	e->trans_speed  = 10.0;
	e->rot_speed = 13.0;
	//e->cam = NULL;
	//init_camera_axes(&e->cam);
	//e->lock_x = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	//pthread_mutex_init(&e->lock_x, NULL);
	//e->cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;;
	//e->stack = NULL;
	e->num_thread = (int)THREADS;
	e->thread_array = NULL;
	return (e);
}
