#include "../includes/rt.h"

void	min_vector(t_vector *min, t_vector a, t_vector b)
{
	min->x = MIN(a.x, b.x);
	min->y = MIN(a.y, b.y);
	min->z = MIN(a.z, b.z);
}

void	max_vector(t_vector *min, t_vector a, t_vector b)
{
	min->x = MAX(a.x, b.x);
	min->y = MAX(a.y, b.y);
	min->z = MAX(a.z, b.z);
}

void		sphere_thinring_min_max(t_obj *obj)
{
	if (!ft_strcmp(obj->name, "\tsphere"))
	{
		obj->min_pos = add_bias(-obj->radius - BIAS, obj->center);
		obj->max_pos = add_bias(obj->radius + BIAS, obj->center);
	}
	if (!ft_strcmp(obj->name, "\tthinring"))
	{
		obj->min_pos.x = obj->center.x - obj->a - BIAS;
		obj->min_pos.y = obj->center.y - obj->c - BIAS;
		obj->min_pos.z = fabs(obj->a - obj->b);

		obj->min_pos.x = obj->center.x + obj->a + BIAS;
		obj->min_pos.y = obj->center.y + obj->c + BIAS;
		obj->min_pos.z = fabs(obj->a - obj->b);
	}
}

void		cylinder_or_cone__min_max(t_obj *obj)
{
	double cos;

	if (!ft_strcmp(obj->name, "\tcylinder") || !ft_strcmp(obj->name, "\tcone"))
	{
			normalize(&obj->axe);
			cos = prodscal(obj->axe, (t_vector){1.0f, 0.0f, 0.0f});
			obj->min_pos = add_bias(-normevect(subvect(obj->cut_point, obj->center)) * fabs(cos) - BIAS, obj->center);
			obj->max_pos = add_bias(normevect(subvect(obj->cut_point, obj->center)) * fabs(cos) + BIAS, obj->center);
	}
}

void		triangle_min_max(t_obj *obj)
{

	if (!ft_strcmp(obj->name, "\ttriangle"))
	{
		min_vector(&obj->min_pos, obj->v0, obj->v1);
		min_vector(&obj->min_pos, obj->min_pos, obj->v2);
		max_vector(&obj->max_pos, obj->v0, obj->v1);
		max_vector(&obj->max_pos, obj->max_pos, obj->v2);
	}
}

void		torus_min_max(t_obj *obj)
{

	float cos;

	if (!ft_strcmp(obj->name, "\ttorus"))
	{
			normalize(&obj->axe);
			cos = prodscal(obj->axe, (t_vector){1.0f, 0.0f, 0.0f});
			obj->min_pos = add_bias(-obj->a  * fabs(cos) - BIAS, obj->center);
			obj->max_pos = add_bias(obj->a  * fabs(cos) + BIAS, obj->center);
	}
}

void		cube_boxe_min_max(t_obj *obj)
{
	if (!ft_strcmp(obj->name, "\tcuboid") || !ft_strcmp(obj->name, "\tblock") ||  !ft_strcmp(obj->name, "\trick") || !ft_strcmp(obj->name, "\tchessboard") || !ft_strcmp(obj->name, "\tbox"))
	{
		obj->min_pos = add_bias(-obj->radius - BIAS, obj->center);
		obj->max_pos = add_bias(obj->radius + BIAS, obj->center);
	}
}



/*void		min_max_obj(t_obj *obj, t_vector *min, t_vector *max)
{

}*/

void		init_aabb_box(t_scene *scene)
{
	t_obj *tmp;

	tmp = scene->obj;
	scene->aabb.min = (t_vector){INFINI, INFINI, INFINI };
	scene->aabb.max = (t_vector){-INFINI, -INFINI, -INFINI };
	while(tmp)
	{
		sphere_thinring_min_max(tmp);
		cylinder_or_cone__min_max(tmp);
		triangle_min_max(tmp);
		torus_min_max(tmp);
		cube_boxe_min_max(tmp);
		tmp = tmp->next;
	}
	tmp = scene->obj;
	while(tmp)
	{
		min_vector(&scene->aabb.min, scene->aabb.min, tmp->min_pos);
		max_vector(&scene->aabb.max, scene->aabb.max, tmp->max_pos);
		tmp = tmp->next;
	}
}
