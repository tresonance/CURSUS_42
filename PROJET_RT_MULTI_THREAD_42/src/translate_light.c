
#include "../includes/rt.h"



void		translate_light(int key, t_env *e)
{
	t_light *light;
	
	if (e && e->scene)
	{
		light = e->scene->light;
		while(light)
		{
			if (key == Q)
				light->pos.x += (light->pos.x < WIDTH/2)? 10.0: 0.0;
			if (key == W)
				light->pos.x -= (light->pos.x > -WIDTH/2 )? 10.0 : 0.0;
			if (key == E)
				light->pos.y += (light->pos.y < HEIGHT/2) ? 10.0: 0.0;
			if (key == D)
				light->pos.y -= (light->pos.y > -HEIGHT/2) ? 10.0 : 0.0;
			if (key == A)
				light->pos.z += 10.0;
			if (key == S)
				light->pos.z -= 10.0;
			light = light->next;
		}
	}
}


