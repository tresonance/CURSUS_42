
#include "../includes/rt.h"
#define USCALE 0.05
#define VSCALE 0.05

t_color		get_plane_texture_color(t_hit *inter, t_env *e)
{
	//t_texture *tex;
	t_vector t;
	float hypo;
	float alpha;
	t_vector tmp;
	float ux, uy;

	/*if (inter->obj->tag < 1 || inter->obj->tag > e->total_texture)
	{
		destroy_all(&e);
		err_exit("wrong tag number.\n");
	}*/
	//tex = e->texture_arr[inter->obj->tag - 1];
	t = crossvect(inter->obj->axe, inter->obj->base.sdir);
	if (fabs(normevect(t)) < (double)EPSILON)
		t = crossvect(inter->obj->axe, inter->obj->base.tdir);
	normalize(&t);
	//clcul hypothenuse
	hypo = normevect(subvect(inter->point, inter->obj->center));
	tmp = subvect(inter->obj->center, inter->point);
	normalize(&tmp);
	alpha = acosf(prodscal(t, tmp ));
	if (alpha > 1.508)   //PI / 2
	{
		opposite(&t);
		alpha = acosf(prodscal(t, tmp ));

	}
	//use pythagore theorem to calculate side
	ux = sin(alpha /* M_PI/180.0*/) * hypo / 90.0f;
	uy = cos(alpha /* M_PI/180.0*/) * hypo / 90.0f;
	return (texture_color(e, inter, ux, uy));
	//return(texture_rgb(u, v, tex));

}



