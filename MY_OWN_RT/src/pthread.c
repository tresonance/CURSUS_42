#include "../includes/rt.h"
#define THREAD_STACK_SIZE 4096
//pthread_mutex_t  lock_x = PTHREAD_MUTEX_INITIALIZER;
void		initialize_thread(t_env *e)
{
	int i;
	
	i = -1;
	if(!(e->thread_array = (t_thread*)malloc(e->num_thread * sizeof(t_thread))))
		err_exit("Unable to load thread\n");
	while (++i < e->num_thread)
	{
		e->thread_array[i].arg.id = i;
		e->thread_array[i].arg.color = (t_color){0, 0, 0};
		e->thread_array[i].arg.depth = 0;;
		e->thread_array[i].arg.mlx = e;;

		//x +=  (WIDTH / e->num_thread);
	//	if (x >= WIDTH)
	//	{
	//		x = 0;
	//	}
	}
}


void		*one_thread_render(void *arg)
{
	int x;
	int y;
	t_thread_arg thread_arg;
	
	if (arg == (void*)0 || 0 >=  (int)THREADS)
		err_exit("wrong thread in pthread.c\n");
	thread_arg = *((t_thread_arg*)arg);
	//pthread_mutex_lock(&lock_x);
	y =  (thread_arg.id * HEIGHT / thread_arg.mlx->num_thread) - 1;
	while (++y < ((thread_arg.id + 1) * HEIGHT / thread_arg.mlx->num_thread))
	{
		x =  - 1;
		while (++x < WIDTH)
		{
			//thread_arg.depth = 0;
			current_ray((double)x, (double)y, thread_arg.mlx, &thread_arg.ray);

			thread_arg.color = tracer(thread_arg.ray, thread_arg.depth, thread_arg.mlx);
			ft_clamp_color(&thread_arg.color, 0.0, 1.0);
	//pthread_mutex_lock(&thread_arg.mlx->lock_x);
			pixel_put(x, y, thread_arg.color, thread_arg.mlx);
	//pthread_mutex_unlock(&thread_arg.mlx->lock_x);

		}
	}
	pthread_exit(NULL);
	//return (NULL);
}

void		all_thread_render(t_env *e)
{
	int i;

	i = -1;
	initialize_thread(e);
	while (++i < e->num_thread)
	{
		if (pthread_create((void*)&e->thread_array[i].thread, NULL, one_thread_render, (void*)&e->thread_array[i].arg) == -1)
				err_exit("Unable to create thread from pthread.c\n");
		if (pthread_join(e->thread_array[i].thread, NULL) != 0)
			err_exit("Could not join thread\n");

	}
	i = -1;
	/*while (++i < e->num_thread)
	{
		if (pthread_join(e->thread_array[i].thread, NULL) != 0)
			err_exit("Could not join thread\n");
	}*/
	pthread_mutex_destroy(&e->lock_x);
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);

	display_cam_info(e);
	if (e->is_obj_selected == TRUE)
	{
		display_selected_obj_info1(e);
		display_selected_obj_info2(e);
	}
	//e && e->hit_obj != NULL ? ft_memdel(e->hit_obj) : 0;
	//e->is_obj_selected = FALSE;
}
