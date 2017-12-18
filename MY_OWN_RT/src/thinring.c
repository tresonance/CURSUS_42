/*

#include "../includes/rt.h"

void		orientation_thinring(double *coef, t_vector dist, t_ray r, t_vector axe)
{
	if(axe.x && axe.z)
	{
		coef[0] = r.dir.x * r.dir.x + r.dir.z * r.dir.z;
		coef[1] = 2.0 * (r.dir.x * dist.x + r.dir.z * dist.z);
		coef[2] = (dist.x * dist.x) + (dist.z * dist.z);
	}
	else if(axe.x && axe.y)
	{
		coef[0] = r.dir.x * r.dir.x + r.dir.y * r.dir.y;
		coef[1] = 2.0 * (r.dir.x * dist.x + r.dir.y * dist.y);
		coef[2] = (dist.x * dist.x) + (dist.y * dist.y);
	}
	else if(axe.y && axe.z)
	{
		coef[0] = r.dir.y * r.dir.y + r.dir.z * r.dir.z;
		coef[1] = 2.0 * (r.dir.y * dist.y + r.dir.z * dist.z);
		coef[2] = (dist.y * dist.y) + (dist.z * dist.z);
	}


}

void		append_thinring_cercle_b(t_obj *thinring, t_ray ray, t_hit **hit_list)
{
	t_vector dist;
	double coef[3];
	double roots[2];
	int num_sol;
	int i;
	t_vector point;
	t_hit *new;
	t_ray r;

	r.dir = objectdir_from_cameradir(ray.dir, thinring->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, thinring->center, thinring->base);
	dist = subvect(r.pos, thinring->center);
	orientation_thinring(&coef[0], dist, r,thinring->axe);
	coef[2] -= thinring->b * thinring->b;
	num_sol = second_degre(coef, roots);
	i = -1;
	while (++i < num_sol)
	{
		if (roots[i] > (double)EPSILON)
		{
			point = addvect(r.pos, scalevect(roots[i], r.dir));
			if (fabs(point.y) <= thinring->c/2 )
			{
				if (!(new = (t_hit*)malloc(sizeof(t_hit))))
					err_exit("Unable to allocate\n");

				new->t = roots[i];
				new->normal = (t_vector){0.0, 0.0, -1.0};
				new->point = point;
				new->obj = thinring;
				new->in_ray = r;
				ft_strcpy(new->tag, "bottom face");
				new->ray_origin = r.pos;
				new->next = NULL;
				add_point_to_intersection_list(hit_list, new);
			}
		}
	}
}

void		append_thinring_cercle_a(t_obj *thinring, t_ray ray, t_hit **hit_list)
{
	t_vector dist;
	double coef[3];
	double roots[2];
	int num_sol;
	int i;
	t_vector point;
	t_hit *new;
	t_ray r;

	r.dir = objectdir_from_cameradir(ray.dir, thinring->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, thinring->center, thinring->base);
	dist = subvect(r.pos, thinring->center);
	orientation_thinring(&coef[0], dist, r,thinring->axe);
	coef[2] -= thinring->a * thinring->a;

	num_sol = second_degre(coef, roots);
	i = -1;
	while (++i < num_sol)
	{
		if (roots[i] > (double)EPSILON)
		{
			point = addvect(r.pos, scalevect(roots[i], r.dir));
			if (fabs(point.y) <= thinring->c/2 )
			{
				if (!(new = (t_hit*)malloc(sizeof(t_hit))))
					err_exit("Unable to allocate\n");

				new->t = roots[i];
				new->normal = (t_vector){0.0, 0.0, -1.0};
				new->point = point;
				new->obj = thinring;
				new->in_ray = r;
				ft_strcpy(new->tag, "bottom face");
				new->ray_origin = r.pos;
				new->next = NULL;
				add_point_to_intersection_list(hit_list, new);
			}
		}
	}
}
*/

#include "../includes/rt.h"
void		append_thinring_disc(t_obj *thinring, t_ray ray, t_hit **hit_list)
{
	t_vector point;
	t_hit *new;
	t_ray r;
	double t;
	double dist_squar;

	r.dir = objectdir_from_cameradir(ray.dir, thinring->base);
	normalize(&(r.dir));
	r.pos = objectpoint_from_camerapoint(ray.pos, thinring->center, thinring->base);

	if (fabs(r.dir.y) > (double)EPSILON)
	{
		t = (thinring->c - r.pos.y) / r.dir.y;
		if (t > (double)EPSILON)
		{
			point = addvect(r.pos, scalevect(t, r.dir));
			dist_squar = (point.x * point.x) + (point.z * point.z);
			if ((thinring->b * thinring->b <= dist_squar + (double)EPSILON)  && (dist_squar  <= thinring->a * thinring->a + (double)EPSILON))
			{
				if (!(new = (t_hit*)malloc(sizeof(t_hit))))
					err_exit("Unable to allocate\n");

				new->t = t;
				new->normal = (t_vector){0.0, (r.pos.z >= 0.0) ? +1.0 : -1.0, 0.0};
				new->point = (t_vector){point.x, 0.0, point.z};
				new->displacement = normevectsquar(scalevect(t, r.dir));
				new->obj = thinring;
				//new->in_ray = r;
				new->ray_origin = r.pos;
				new->next = NULL;
				add_point_to_intersection_list(hit_list, new);

			}
		}
	}
}

void		append_thinring(t_obj *thinring, t_ray ray, t_hit **hit_list)
{
	//append_thinring_cercle_b(thinring, ray, hit_list);
	//append_thinring_cercle_a(thinring, ray, hit_list);
	append_thinring_disc(thinring, ray, hit_list);
}

t_color			get_thinring_texture_color(t_hit *inter, t_env *e){
	return (get_cylinder_texture_color(inter, e));
}
