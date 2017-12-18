#include "rt.h"

void	box_normal(t_hit *hit, t_ray *ray, t_vector *pos)
{
		t_vector tmp;
		t_vector tmpf;
		float m;
		t_vector left;
		t_vector right;
		t_vector vec;

		m = 1.0001f;
		left  = scalevect(0.5f, addvect(pos[0],  pos[1]));
		vec = subvect(hit->point, left);
		right = scalevect(0.5f, subvect(pos[0], pos[1]));
		tmpf.x = vec.x / fabs(right.x) * m;
		tmpf.y = vec.y / fabs(right.y) * m;
		tmpf.z = vec.z / fabs(right.z) * m;
		tmp.x = (int)tmpf.x;
		tmp.y = (int)tmpf.y;
		tmp.z = (int)tmpf.z;
		hit->normal.x = (float)tmp.x;
		hit->normal.y = (float)tmp.y;
		hit->normal.z = (float)tmp.z;
		if (prodscal(ray->dir, hit->normal) > 0.0f)
			opposite(&hit->normal);
}

static void	box_utils(t_ray ray, int signe[3], t_vector *invdir)
{

		invdir->x = 1.0f / ray.dir.x;
		invdir->y = 1.0f / ray.dir.y;
		invdir->z = 1.0f / ray.dir.z;
		signe[0] = (invdir->x < 0.0f);
		signe[1] = (invdir->y < 0.0f);
		signe[2] = (invdir->z < 0.0f);
	}


static float	box_inter(t_obj obj, t_ray *r, t_vector *pos)
{
		float txmin;
		float txmax;
		float tymin;
		float tymax;
		float tzmin;
		float tzmax;
		t_vector  invdir;
		//t_vector pos2;

		int	signe[3];
		//pos[0] = subvect(obj.center, (t_vector){obj.a/2, obj.a/2, obj.a/2 });
		pos[0] = (t_vector){-obj.a/2, -obj.b/2, -obj.c/2 };
		pos[1] = (t_vector){obj.a/2, obj.b/2, obj.c/2 };
		//pos[1] = addvect(obj.center, (t_vector){obj.a/2, obj.a/2, obj.a/2 });
		//pos2->y = obj.a;
		//pos2->z = obj.a;
		const t_vector	arr[2] = {pos[0], pos[1]};


		box_utils(*r, &signe[0], &invdir);
		txmin = (arr[signe[0]].x - r->pos.x) * invdir.x ;
		txmax = (arr[1 - signe[0]].x - r->pos.x) * invdir.x;
		tymin = ( arr[signe[1]].y - r->pos.y) * invdir.y;
		tymax = (arr[1 - signe[1]].y - r->pos.y) * invdir.y;

		if ((txmin > tymax) || (tymin > txmax))
			return (-1);
		if (tymin > txmin)
			txmin = tymin;
		if (tymax < txmax)
			txmax = tymax;
		tzmin = (arr[signe[2]].z - r->pos.z) * invdir.z;
		tzmax = (arr[1 - signe[2]].z - r->pos.z) * invdir.z;
		if ((txmin > tzmax) || (tzmin > txmax))
			return(-1);
		if (tzmin > txmin)
			txmin = tzmin;
		if (tzmax < txmax)
			txmax = tzmax;
		if (txmin > 0.0f && txmin < txmax)
			return (txmin);
		return (txmax);
}

void		append_box(t_obj *box, t_ray ray, t_hit **hit_list)
{
		float t;
		t_vector point;
		t_ray r;
		t_hit *new;
		t_vector pos[2];

		r.dir = objectdir_from_cameradir(ray.dir, (*box).base);
		normalize(&(r.dir));
		r.pos = objectpoint_from_camerapoint(ray.pos, (*box).center,
				(*box).base);
		t = box_inter(*box, &r, &pos[0]);
		if (t > 0 && t < INFINI)
		{
			point = addvect(r.pos, scalevect(t, r.dir));
			if (!(new = (t_hit*)malloc(sizeof(t_hit))))
				err_exit("Unable to allocate\n");
			new->displacement = normevectsquar(scalevect(t, r.dir));
			box_normal(new, &r, &pos[0]) ;
			set_inter_info1(&new, t, new->normal, point);
			set_inter_info2(&new, &box, ray, ray.pos);
			add_point_to_intersection_list(hit_list, new);
		}
}
