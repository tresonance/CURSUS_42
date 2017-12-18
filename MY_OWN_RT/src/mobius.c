
#include "../includes/rt.h"

t_vector		mobius_normal(t_obj *mobius, t_vector p)
{
	t_vector normal;

	normal.x = 2.0 * p.x * p.y - 2.0 * mobius->a * p.z - 4.0 * p.x * p.z;
	normal.y = -mobius->a * mobius->a + p.x * p.x + 3.0  * p.y * p.y - 4.0 * p.y * p.z + p.z * p.z;
	normal.z = -2.0 * mobius->a * p.x - 2.0 * p.x * p.x - 2.0 * p.y * p.y + 2.0 * p.y * p.z;
	normalize(&normal);
	return (normal);
}

void	append_mobius(t_obj *mobius, t_ray ray, t_hit **hit_list)
{
	t_polyn  poly;
	int num_sol;
	int i;
	t_hit *new;
	t_vector point;
	double roots[3];
	t_ray r;

	//intersection with lateral faces

	r.dir = objectdir_from_cameradir(ray.dir, mobius->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, mobius->center, mobius->base);
	poly.a = 0.0;
	poly.b = r.dir.x * r.dir.x * r.dir.y + r.dir.y * r.dir.y * r.dir.y - 2.0 *r.dir.x * r.dir.x * r.dir.z - 2.0 * r.dir.y * r.dir.y *  r.dir.z + r.dir.y * r.dir.z * r.dir.z;

	poly.c = 2.0 * r.pos.x * r.dir.x * r.dir.y + r.pos.y * r.dir.x * r.dir.x + 3.0 * r.pos.y * r.dir.y * r.dir.y - 2.0 * mobius->a * r.dir.x * r.dir.z - 2.0 * r.dir.x * r.dir.x * r.pos.z - 4.0 * r.pos.x * r.dir.x * r.dir.z - 4.0 * r.pos.y * r.dir.y * r.dir.z  - 2.0 * r.dir.y * r.dir.y * r.pos.z + r.pos.y * r.dir.z * r.dir.z + 2.0 * r.pos.z * r.dir.z * r.dir.y;

	poly.d = -mobius->a * mobius->a * r.dir.y + r.pos.x * r.pos.x * r.dir.y + 2.0 * r.pos.x * r.dir.x * r.pos.y + 3.0 * r.pos.y * r.pos.y * r.dir.y - 2.0 * mobius->a * (r.pos.x * r.dir.z + r.pos.z * r.dir.x ) - 2.0 * r.pos.x * r.pos.x * r.dir.z -4.0 * r.pos.x * r.pos.z * r.dir.x - 2.0 * r.pos.y * r.pos.y * r.dir.z - 4.0 * r.pos.y * r.dir.y * r.pos.z + 2.0 * r.pos.y * r.pos.z * r.dir.z + 2.0 * r.pos.y * r.pos.z * r.dir.z + r.pos.z * r.pos.z * r.dir.y;
	
	poly.e = -mobius->a * mobius->a * r.pos.y + r.pos.x * r.pos.x * r.pos.y + r.pos.y * r.pos.y * r.pos.y - 2.0 * mobius->a * r.pos.x * r.pos.z - 2.0 * r.pos.x * r.pos.x * r.pos.z - 2.0 * r.pos.y * r.pos.y * r.pos.z + r.pos.y * r.pos.z * r.pos.z;
	
	/*t_vector dist = subvect(r.pos, mobius->center);
	coef[0] = (r.dir.x * r. dir.x) + (r.dir.z * r.dir.z);
	coef[1] = 2.0 * (r.dir.x * dist.x) + (r.dir.z * dist.z);
	coef[2] = (dist.x * dist.x) + (dist.z * dist.z) - (mobius->radius * mobius->radius);*/
	num_sol = cubic(poly, roots);
	i = -1;
	while (++i < num_sol)
	{
		if (roots[i] > (double)EPSILON)
		{
			//we found an intersection with the infinitely-extended lateral
			//but the z-component must be + or -zdis
			point.x = r.pos.x + (roots[i] * r.dir.x);
			point.y = r.pos.y + (roots[i] * r.dir.y);
			point.z = r.pos.z + (roots[i] * r.dir.z);

			if (is_hit_point_already_inside(point, *hit_list) == FALSE && normevectsquar(point) <= mobius->a * mobius->a)
			{
				if (!(new = (t_hit*)malloc(sizeof(t_hit))))
					err_exit("Unable to allocate\n");
				new->t = roots[i];
				new->point = point;
				new->obj = mobius;
				//new->in_ray = ray;
				ft_strcpy(new->tag, "lateral");
				new->ray_origin = ray.pos;
				new->displacement = normevectsquar(scalevect(roots[i], r.dir));
			//t_vector dist = subvect(r.pos, mobius->center);
			//double m = roots[i] * prodscal(r.dir, mobius->axe) + prodscal(dist, mobius->axe);
			//t_vector left = subvect(point, mobius->center);
			//t_vector right = scalevect(m, mobius->axe);
			//new->normal = subvect(left, right);
			//new->normal = subvect(point, mobius->center);
			new->next = NULL;
			//new->normal = (t_vector){point.x, 0.0, point.z };
			//normalize(&new->normal);
			new->normal = mobius_normal(mobius, point);
			add_point_to_intersection_list(hit_list, new);
			}
		}
	}
}

t_color		get_mobius_texture_color(t_hit *inter, t_env *e)
{
		return(get_cylinder_texture_color(inter, e));
}
