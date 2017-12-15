#include "rt.cl.h"
#include "resolution.cl"

static float	solver(float a, float b, float c)
{
	float	delta;
	float	t1;
	float	t2;

	delta = b * b - 4.0f * a * c;
if (delta < 0.0001)
		return (-1);
	else if (delta == 0)
		return (-0.5f * b / a);
	t1 = 0.5 * (-1.0 * b - sqrt(delta)) / a;
	t2 = 0.5 * (-1.0 * b + sqrt(delta)) / a;
	if (t1 >= 0.0001 && t2 >= 0.0001)
		return (t1 < t2 ? t1 : t2);
	else if (t1 * t2 <= 0.0001)
		return (t1 >= 0.0001 ? t1 : t2);
	else
		return (-1.0);
}

static float	solver_negatif(float a, float b, float c)
{
	float	delta;
	float	t1;
	float	t2;

	delta = b * b - 4.0f * a * c;
	if (delta < 0.0001)
		return (-1);
	else if (delta == 0)
		return (-0.5f * b / a);
	t1 = 0.5 * (-1.0 * b - sqrt(delta)) / a;
	t2 = 0.5 * (-1.0 * b + sqrt(delta)) / a;
	if (t1 >= 0.0001 && t2 >= 0.0001)
		return (t1 > t2 ? t1 : t2);
	else if (t1 * t2 <= 0.0001)
		return (t1 >= 0.0001 ? t1 : t2);
	else
		return (-1.0);
}

void		cut_obj(float4 pos1, t_ray *ray, float *t)
{
	float4 hit;
	float4 plan_point;
	float4 vec;

	plan_point.x = pos1.x * pos1.w;
	plan_point.y = pos1.y * pos1.w;
	plan_point.z = pos1.z * pos1.w;
	plan_point.w = 1.0f;

	hit = ray->pos + ray->dir * (*t);
	vec = hit - plan_point;
	normalize(vec);
	normalize(pos1);
	if(dot(vec, pos1) > 0.0f)
		*t = -1.0f;
}

static float	sphere_inter(t_prim prim, t_ray *ray, int flag)
{
	float	t;
	float4	dist;
	float	a;
	float	b;
	float	c;

	dist = ray->pos - prim.pos;
	a = dot(ray->dir, ray->dir);
	b = 2.0 * dot(ray->dir, dist);
	c = dot(dist, dist) - (prim.size * prim.size);
	if (flag == 1)
		t = solver(a, b, c);
	else
		t = solver_negatif(a, b, c);
	cut_obj(prim.pos1, ray, &t);
	return (t);
}

static float	cylinder_inter(t_prim prim, t_ray *ray)
{
	float	t;
	float4	dist;
	float	a;
	float	b;
	float	c;

	dist = ray->pos - prim.pos;
	prim.rot = normalize(prim.rot);
	a = dot(ray->dir, ray->dir) - pow(dot(prim.rot, ray->dir), 2);
	b = 2.0 * (dot(dist, ray->dir) - (dot(prim.rot, dist) * dot(prim.rot, ray->dir)));
	c = dot(dist, dist) - pow(dot(prim.rot, dist), 2) - prim.size * prim.size;
	t = solver(a, b, c);
	cut_obj(prim.pos1, ray, &t);
	return (t);
}

static float	cone_inter(t_prim prim, t_ray *ray)
{
	float	t;
	float4	dist;
	float	a;
	float	b;
	float	c;

	dist = ray->pos - prim.pos;
	prim.rot = normalize(prim.rot);
	a = dot(ray->dir, ray->dir) - (1 + pow(tan(prim.size), 2)) * pow(dot(ray->dir, prim.rot), 2);
	b = 2.0 * (dot(ray->dir, dist) - (1 + pow(tan(prim.size), 2)) *
			dot(ray->dir, prim.rot) * dot(dist, prim.rot));
	c = dot(dist, dist) - (1 + pow(tan(prim.size), 2)) * pow(dot(dist, prim.rot), 2);
	t = solver(a, b, c);
	cut_obj(prim.pos1, ray, &t);
	return (t);
}

static float	plane_inter(t_prim prim, t_ray *ray)
{
	float	t;
	float4	dist;

	dist = ray->pos - prim.pos;
	t = -1.0 * dot(prim.rot, dist) / dot(prim.rot, ray->dir);
	cut_obj(prim.pos1, ray, &t);
	return (t < 0.0001 ? -1 : t);
}

static float	triangle_inter(t_prim prim, t_ray *ray)
{
	float a;
	float f;
	float u;
	float v;
	float4 h;
	float4 s;
	float4 q;
	float4 edge1;
	float4 edge2;
	float	t;

	edge1 = prim.pos1 - prim.pos;
	edge2 = prim.pos2 - prim.pos;
	h = cross(ray->dir, edge2);
	a = dot(edge1, h);
	if (a >= -TOLERANCE && a <= TOLERANCE)
		return (-1);
	f = 1.0 / a;
	s = ray->pos - prim.pos;
	u = f * dot(s, h);
	if (u < 0.0 || u > 1.0)
		return (-1);
	q = cross(s, edge1);
	v = f * dot(ray->dir, q);
	if (v < 0.0 || u + v > 1.0)
		return (-1);
	t = f * dot(edge2, q);
	cut_obj(prim.rot, ray, &t);
	return(t < 0.0001 ? -1 : t);
}

static void	box_utils(t_ray ray, int signe[3], float4 *invdir)
{

	*invdir = 1.0f / ray.dir;
	signe[0] = (invdir->x < 0.0f);
	signe[1] = (invdir->y < 0.0f);
	signe[2] = (invdir->z < 0.0f);
}

static float	box_inter(t_prim prim, t_ray *ray)
{
	float	txmin;
	float	txmax;
	float	tymin;
	float	tymax;
	float	tzmin;
	float	tzmax;
	float4	invdir;

	int		signe[3];
	const float4	arr[2] = {prim.pos1, prim.pos2};

	box_utils(*ray, &signe[0], &invdir);
	txmin = (arr[signe[0]].x - ray->pos.x) * invdir.x ;
	txmax = (arr[1 - signe[0]].x - ray->pos.x) * invdir.x;
	tymin = ( arr[signe[1]].y - ray->pos.y) * invdir.y;
	tymax = (arr[1 - signe[1]].y - ray->pos.y) * invdir.y;

	if ((txmin > tymax) || (tymin > txmax))
		return (-1);
	if (tymin > txmin)
		txmin = tymin;
	if (tymax < txmax)
		txmax = tymax;
	tzmin = (arr[signe[2]].z - ray->pos.z) * invdir.z;
	tzmax = (arr[1 - signe[2]].z - ray->pos.z) * invdir.z;
	if ((txmin > tzmax) || (tzmin > txmax))
		return(-1);
	if (tzmin > txmin)
		txmin = tzmin;
	if (tzmax < txmax)
		txmax = tzmax;
	if (txmin > 0.0f && txmin < txmax)
	{
		cut_obj(prim.rot, ray, &txmin);
		return (txmin);
	}
	else
	{
		cut_obj(prim.rot, ray, &txmax);
		return (txmax);
	}
}

static float	paraboloid_inter(t_prim prim, t_ray *ray)
{
	float a;
		float b;
	float c;
	float4 dist;
	float t;

	dist = ray->pos - prim.pos;
	a = dot(ray->dir, ray->dir) - (dot(prim.rot, ray->dir) * dot(prim.rot, ray->dir));
	b = 2.0 * (dot(dist, ray->dir) - dot(prim.rot, ray->dir) * ((dot(prim.rot, dist) + 2.0 * prim.size)));
	c = dot(dist, dist) - (dot(prim.rot, dist) * (dot(dist, prim.rot) + 4.0 * prim.size));
	t = solver(a, b, c);
	cut_obj(prim.pos1, ray, &t);
	return (t);
}

static	float	tore_inter(t_prim prim, t_ray *ray)
{
	float	t;

	t = degre4_solver(prim, ray);
	//cut_obj(prim.pos2, ray, &t);
	return (t);

}

static float	intersect_utils(t_ray *ray, t_scene *scene, int *prim_id)
{
	int		i;
	float	t;
	float	mint;

	i = 0;
	t = MAXRENDERDIST;
	mint = MAXRENDERDIST;
	while (i < scene->info->nb_prim)
	{
		if (scene->prim[i].type == SPHERE || scene->prim[i].type == SKY)
			t = sphere_inter(scene->prim[i], ray, 1);
		else if (scene->prim[i].type == PLANE)
			t = plane_inter(scene->prim[i], ray);
		else if (scene->prim[i].type == CONE)
			t = cone_inter(scene->prim[i], ray);
		else if (scene->prim[i].type == CYLINDER)
			t = cylinder_inter(scene->prim[i], ray);
		else if (scene->prim[i].type == TRIANGLE)
			t = triangle_inter(scene->prim[i], ray);
		else if (scene->prim[i].type == BOX)
			t = box_inter(scene->prim[i], ray);
		else if (scene->prim[i].type == PARABOLOID)
			t = paraboloid_inter(scene->prim[i], ray);
		else if (scene->prim[i].type == TORE)
			t = tore_inter(scene->prim[i], ray);


		if (0.0001f < t && t < mint)
		{
			mint = t;
			*prim_id = i;
		}
		i++;
	}
	return (mint);
}

static float	intersect(t_ray *ray, t_scene *scene, int *prim_id)
{
	float t;

	t = intersect_utils(ray, scene, prim_id);
	if (t > 0.0f && scene->prim[*prim_id].type == SPHERE && scene->prim[*prim_id].size < 0.0f)
	{
		t =  sphere_inter(scene->prim[*prim_id], ray, 2);
		ray->pos = ray->pos + (t * ray->dir) + 0.001f * ray->dir;
		*prim_id = -1;
		return(intersect_utils(ray, scene, prim_id));
	}
	return (t);
}