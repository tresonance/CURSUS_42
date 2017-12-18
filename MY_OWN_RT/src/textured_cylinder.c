
#include "../includes/rt.h"
#define USCALE 0.05
#define VSCALE 0.05


t_color		get_cylinder_texture_color(t_hit *inter, t_env *e)
{
	t_texture *tex;
	float theta;
	float z;

	if (inter->obj->tag < 1 || inter->obj->tag > e->total_texture)
	{
		destroy_all(&e);
		err_exit("wrong tag number.\n");
	}
	tex = e->texture_arr[inter->obj->tag - 1];
	//inter->point = objectpoint_from_camerapoint(inter->point, inter->obj->center, inter->obj->base);
	theta = atan2(inter->point.z ,  inter->point.x);
	z = inter->point.y;
	return (texture_rgb(theta / (2.0 * M_PI) * tex->width, z / ((float)tex->height) , tex));
}
