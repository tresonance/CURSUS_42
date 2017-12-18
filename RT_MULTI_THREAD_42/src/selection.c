#include "../includes/rt.h"


int			selected_obj_info(int x, int y, t_env *e, t_hit *inter)
{
	t_ray		ray;

	current_ray((double)x, (double)y, e, &ray);
	//t = find_closest_t(e->obj, &ray, &e->hit_obj);
	
	if (0 != findclosest_intersection(e, ray, &inter))
	{
		//e->hit_obj->current = 0;
		e->hit_obj = inter->obj;
		e->is_obj_selected = TRUE;
		return (TRUE);
	}
	return (FALSE);
}


int				mouse_hook_func(int button, int x, int y, t_env *e)
{
	t_hit *inter;

	inter = NULL;
	e->is_obj_selected = FALSE;
	e->hit_obj = NULL;
	if (button == 1 && x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if(TRUE == selected_obj_info(x, y, e, inter))
		{
			if (e->is_obj_selected == TRUE)
				all_thread_render(e);
		}
		else
			mlx_string_put(e->mlx, e->win, x, y, 0x00FEDC, "N0 SELECTION");
	}
	//e->is_obj_selected = FALSE;
	e->is_obj_selected == TRUE ? destroy_intersection_list(&inter) : 0;
	e->is_obj_selected = FALSE;
	return (0);
}
