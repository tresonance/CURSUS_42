
#include "../includes/rt.h"
#define USCALE 0.05
#define VSCALE 0.05

int		pondere(t_obj *triangle, t_vector p, float *lamdha)
{
	t_obj *t;
	float deno;

	t = triangle;
	deno = ((t->v1.y - t->v2.y) * (t->v0.x - t->v2.x)) + ((t->v2.x - t->v1.x) * (t->v0.y - t->v2.y));
	if (fabs(deno) < (float)EPSILON)
	{	
		ft_putstr("deno too closer to zero in textured_triangle.c\n");
		return (0);
	}
	lamdha[0] = (((t->v1.y - t->v2.y) * (p.x - t->v2.x)) + ((t->v2.x - t->v1.x) * (p.y - t->v2.y))) / deno;

	lamdha[1] = (((t->v2.y - t->v0.y) * (p.x - t->v2.x)) + ((t->v0.x - t->v2.x) * (p.y - t->v2.y))) / deno;

	lamdha[2] = 1.0 - lamdha[0] - lamdha[1];
	return (1);
}

int		barycentre_ratio(t_obj *triangle, t_vector p,float *ratio)
{
	float lamdha[3];
	float deno;
	
	if (0 == pondere(triangle, p, &lamdha[0]))
		return (0);
	deno = (1.0 /lamdha[0]) + (1.0 / lamdha[1]) + (1.0 / lamdha[2]);
	if (fabs(deno) < (float)EPSILON)
		return (0);
	ratio[0] = (1.0 / lamdha[0]) / deno;
	ratio[1] = (1.0 / lamdha[1]) / deno;
	ratio[2] = (1.0 / lamdha[2]) / deno;
	return (1);
}

t_color		get_triangle_texture_color(t_hit *inter, t_env *e)
{
	t_texture *tex;
	float ratio[0];

	if (inter->obj->tag < 1 || inter->obj->tag > e->total_texture)
	{
		destroy_all(&e);
		err_exit("wrong tag number.\n");
	}
	tex = e->texture_arr[inter->obj->tag - 1];
	//if (0 == barycentre_ratio(inter->obj, inter->point, &ratio[0]))
	if(0 == pondere(inter->obj, inter->point, &ratio[0]))
	{
		ft_putstr("bad barycenter coordinate from texture_triangle.c;\n");
		return (inter->obj->matte);
	}
	
	return (texture_color(e, inter, ratio[0] , ratio[1]));
}
