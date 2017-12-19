
#include "../includes/rt.h"
#define SHIFT 0.001

//POLARIZED REFLECTION

void		ft_clamp_val(float *val, float  min , float max)
{
	(*val) = ((*val) < min) ? min : (*val);
	(*val) = ((*val) > max) ? max : (*val);
}

double		ft_maxf(float a, float b)
{
	double max;

	max = (a < b) ? b : a;
	return (max);
}

void		ft_swapf(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// ILLUMINATION COLOR

int		is_not_shadowed(t_env *e, t_ray *shadow, t_hit *inter, double light_dist)
{
	//t_ray ray;
	//double dist;
	//t_vector offset;
	//t_hit	*inter;
	int outside;

	//ray.->dir = subvect(p2, p1);
	//dist = normevectsquar(ray.dir);
//	normalize(&ray.dir);
	outside = (prodscal(shadow->dir, inter->normal) < 0.0);
	//offset = scalevect((double)BIAS, ray.dir);
	//shadow->pos = outside ? addvect(inter->point, scalevect(SHIFT, inter->normal)) : subvect(inter->point, scalevect(SHIFT, inter->normal)) ;
	shadow->pos = addvect(inter->point, scalevect(BIAS, inter->normal));
	//ray.pos = p1;
	if (0 != findclosest_intersection(e, *shadow, &inter))
	{
		if (inter->obj->obj_index == shadow->obj_from->obj_index)
			return (TRUE);
		if (inter->obj->is_light_obj)
			return (TRUE);
		if (ft_strcmp(inter->obj->name, "\tplane"))
			return (FALSE);
		if (inter->displacement < light_dist || inter->t > (double)INFINI)
		{
			free(inter);
			return(FALSE);
		}
		free(inter);
	}
	return (TRUE);

}

double		get_specul(t_vector light_vector, t_hit *inter)
{
	t_vector halfway;
	t_vector view;
	double specular;
	
	view = subvect(inter->ray_origin, inter->point);
	normalize(&view);
	halfway = addvect(light_vector, view);
	normalize(&halfway);
	specular = prodscal(inter->normal, halfway);
	specular = (specular > 0.0001) ? specular : 0.0;
	specular = pow(specular, 100);
	return (specular);
}

t_color		calculate_matte_obj(t_hit *inter, t_env *e)
{
	t_light_obj *light_source;
	t_color colorsum;

	t_vector light_vect;
	double cos_teta;
	double dist;
	double intensity;
	//t_obj	*obj;
	double specular;
	t_ray shadow;

	//colorsum = (t_color){0.0, 0.0, 0.0};
	light_source = e->scene->light_obj;
	
	colorsum = scalcol(inter->obj->matte_factor, inter->obj->matte);
	//if(inter->obj->tag != 0)
	//	return (scalcol(inter->obj->matte_factor,inter->obj->matte));
	while (light_source)
	{
		shadow.dir = subvect(light_source->obj->center, inter->point);
		dist = normevectsquar(shadow.dir);
		normalize(&shadow.dir);
		shadow.obj_from = inter->obj;
		shadow.obj_from->obj_index  = inter->obj->obj_index;
		if (TRUE == is_not_shadowed(e, &shadow, inter,  dist))
		{
			light_vect = subvect(light_source->obj->center, inter->point);			
			dist = normevectsquar(light_vect);
			normalize(&light_vect);
			normalize(&inter->normal);
			cos_teta = prodscal(inter->normal, light_vect);
			ft_clamp_val((float*)&cos_teta, -1.0, 1.0);
			cos_teta = (cos_teta < 0.0) ? fabs(cos_teta) : cos_teta;
			if (cos_teta > 0.0)
			{
				intensity = fabs(cos_teta);
				colorsum = addcol(colorsum, scalcol(intensity * inter->obj->glossy_factor, light_source->obj->matte));
				specular = get_specul(light_vect, inter);
				colorsum = addcol(colorsum, scalcol(inter->obj->specular_factor * specular, light_source->obj->glossy));
			}
		}
		light_source = light_source->next;

	}
	return (colorsum);
}

t_color		calculate_matte(t_hit *inter, t_env *e)
{
	t_light *light_source;
	t_color colorsum;

	t_vector light_vect;
	double cos_teta;
	double dist;
	double intensity;
	//t_obj	*obj;
	double specular;
	t_ray shadow;;

	//colorsum = (t_color){0.0, 0.0, 0.0};
	light_source = e->scene->light;
	
	//colorsum = scalcol(inter->obj->matte_factor, inter->obj->matte);
	colorsum = calculate_matte_obj(inter, e);
	//if(inter->obj->tag != 0)
	//	return (inter->obj->matte);
	while (light_source)
	{
		shadow.dir = (light_source->parallel != 0) ? subvect(light_source->pos, inter->point): light_source->pos;
		dist = (light_source->parallel != 0) ? normevectsquar(shadow.dir) : normevectsquar(inter->point) ;
		normalize(&shadow.dir);
		shadow.obj_from = inter->obj;
		shadow.obj_from->obj_index  = inter->obj->obj_index;

		if (TRUE == is_not_shadowed(e,&shadow, inter, dist))
		{
			light_vect = (light_source->parallel != 0) ? subvect(light_source->pos, inter->point): light_source->pos;
			dist = normevectsquar(light_vect);
			normalize(&light_vect);
			normalize(&inter->normal);
			cos_teta = prodscal(inter->normal, light_vect);
			ft_clamp_val((float*)&cos_teta, 0.0, 1.0);
			if (cos_teta > 0.0)
			{
				intensity = cos_teta;
				colorsum = addcol(colorsum, scalcol(intensity * inter->obj->glossy_factor, light_source->color));
				specular = get_specul(light_vect, inter);
				colorsum = addcol(colorsum, scalcol(inter->obj->specular_factor * specular, light_source->color));
			}
		}
		light_source = light_source->next;

	}
	return (colorsum);
}


