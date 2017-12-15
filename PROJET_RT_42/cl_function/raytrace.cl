#include "rt.cl.h"

float4		torus_normal(t_hit hit , t_prim prim)
{
	float4 t;
	float4 s;
	float4	normal;
	float i;
	float j;
	float tmp;

	/*hit_obj_space = hit - prim.pos;
	hit_obj_space.x = dot(hit_obj_space, cam->right);
	hit_obj_space.y = dot(hit_obj_space, cam->up);
	hit_obj_space.z = dot(hit_obj_space, cam->normal);*/

	tmp = hit.point.z / prim.pos1.x;
	i = asin(tmp);
	tmp = hit.point.y / (prim.pos.y + prim.pos1.x * cos(i));
	j = asin(tmp);
	t.x = -sin(j);
	t.y = cos(j);
	t.z = t.x;

	s.x = prim.pos1.y * cos(j) * sin(i);
	s.x = prim.pos1.y * sin(j) * (-sin(i));
	s.z = prim.pos1.y * cos(i);
	s.w = 0.0;
	normal = cross(t, s);
	return (normal);
}

static void	get_hit_point_info(t_hit *hit, t_prim prim, t_ray *ray)
{
	float	m;
	float4	dist;
	float4	left;
	float4	right;
	float4	vec;

	hit->ray_origin = *ray;
	hit->point = ray->pos + ray->dir * hit->t;
	if (prim.type == SPHERE || prim.type == SKY)
		hit->normal = hit->point - prim.pos;
	else if (prim.type == CYLINDER)
	{
		dist = ray->pos - prim.pos;
		m = hit->t * dot(ray->dir, prim.rot) + dot(dist, prim.rot);
		left = hit->point - prim.pos;
		right = prim.rot * m;
		hit->normal = left - right;
	}
	else if (prim.type == CONE)
	{
		dist = ray->pos - prim.pos;
		m = hit->t * dot(ray->dir, prim.rot) + dot(dist, prim.rot);
		left = hit->point - prim.pos;
		right = prim.rot * (1 + pow(tan(prim.rot), 2) * m);
		hit->normal = left - right;
	}
	else if (prim.type == PLANE)
	{
		if (dot(ray->dir, prim.rot) > 0.0f)
			hit->normal = prim.rot * -1.0f;
		else
			hit->normal = prim.rot;
	}
	else if (prim.type == TRIANGLE)
	{
		left = prim.pos1 - prim.pos;
		right = prim.pos2 - prim.pos;
		hit->normal = cross(right, left);
	}
	else if (prim.type == BOX)
	{
		int4	tmp;
		float4	tmpf;

		m = 1.0001f;
		left  = (prim.pos1 + prim.pos2) * 0.5f;
		vec = hit->point - left;
		right = (prim.pos1 - prim.pos2) * 0.5f;
		tmpf = vec / fabs(right) * m;
		tmp = convert_int4(tmpf);
		hit->normal = convert_float4(tmp);
		if (dot(ray->dir, hit->normal) > 0.0f)
			hit->normal *= -1.0f;
	}
	else if (prim.type == PARABOLOID || prim.type == TORE)
	{
		m = dot(hit->point - prim.pos, prim.rot);
		left = hit->point - prim.pos;
		hit->normal = left + ((m + prim.size) * prim.rot);
	}
	else if (prim.type == TORE)
	{
		hit->normal = torus_normal(*hit, prim);
	}
	hit->normal = normalize(hit->normal);
}

static float4	shadow(t_scene *scene, t_light light, t_hit hit)
{
	float	t;
	float	dist;
	float4	l;
	int		hitprim;
	t_ray	ray;
	float4	bias;

	bias.x = 0.0001f;
	bias.y = 0.0001f;
	bias.z = 0.0001f;
	bias.w = 1.0f;
	hitprim = 0;
	l = (float4)(0.0f);
	if (light.type == POINT)
		l = light.pos - hit.point + bias;
	else if (light.type == PARRALEL)
		l = light.dir * -1.0f;
	dist = sqrt(dot(l, l));
	l = normalize(l);
	ray.pos = hit.point + hit.normal;
	ray.dir = l;
	t = intersect(&ray, scene, &hitprim);
	if (((0.0001f < t && t < dist && light.type == POINT) ||
		(t < MAXRENDERDIST && light.type == PARRALEL))/* &&
		hitprim != 0 && hitprim->transparant == 0.0f*/)
		return ((float4)(0.0f));
	return ((float4)(-1.0f));
}

float4	bumpmap(float4 light_dir, float4 n)
{
	float4	t;
	float4	b;
	float4	a;
	float4	v;

	a.xzw = 0.0f;
	a.y = 1.0f;

	t = cross(n, a);
	t = normalize(t);
	b = cross(t, n);
	b = normalize(b);
	v.x = dot(light_dir, t);
	v.y = dot(light_dir, b);
	v.z = dot(light_dir, n);
	v.w = 0.0f;
	v = normalize(v);
	return (v);
}

static float4	get_hit_color(t_scene *scene, t_light light, t_obj hitobj, t_hit hit)
{
	float4	intensity;
	float4	color;
	float4	spec;
	float4	l;
	float4	kd;
	float4	ks;
	float	r2;
	float	dist;
	float	cos_theta;
	float4	s;

	if (light.type == POINT)
	{
		l = light.pos - hit.point;
		r2 = sqrt(dot(l, l));
		l = l / r2;
		intensity = light.color * light.intensity / (float)(4 * M_PI * r2);
	}
	else if (light.type == PARRALEL)
	{
		l = light.dir * -1.0f;
		intensity = light.color * light.intensity;
	}
	s = shadow(scene, light, hit);
	if (s.x > -1.0f)
		return (0.0f);
	if (hitobj.bump.id > 0)
	{
		float	u;
		float	v;
		int		tmpx;
		int		tmpy;

		l = bumpmap(l, hit.normal);
		u = atan2(hit.normal.z, hit.normal.x) / (2.0f * M_PI) + 0.5f;
		v = 0.5f - asin(hit.normal.y) / M_PI;
		u = u > 1.0f ? u - 1.0f : u;
		v = v > 1.0f ? v - 1.0f : v;
		u = min(u, 0.9999f);
		v = min(v, 0.9999f);
		tmpx = u * scene->bump_data->width;
		tmpy = v * scene->bump_data->height;
		hit.normal = scene->bump_image[tmpy * scene->bump_data->width + tmpx];
	}
	cos_theta = max(dot(hit.normal, l), 0.0f);
	color = (hitobj.prim.color / (float)M_PI) * intensity * cos_theta;
	if (light.type != PARRALEL)
	{
		ks = (float4)(0.0f);
		spec = specular(hit, l, hitobj, intensity, cos_theta, &ks);
		color = color + spec;
//		color = spec;
	}
	return (color);
}

static float4	lightning(t_ray *ray, t_scene *scene, t_obj hitobj, float t, t_hit *hit)
{
	t_light	light;
	float4	tmp_color;
	float4	color;
	int		i;

	i = 0;
	hit->t = t;
	color = (float4)(0.0f);
	get_hit_point_info(hit, hitobj.prim, ray);
	while (i < scene->info->nb_light)
	{
		light = scene->light[i];
		tmp_color = get_hit_color(scene, light, hitobj, *hit);
		color += tmp_color;
		i += 1;
	}
	color = clamp(color, 0.0f, 1.0f);
	return (color);
}

static float4	get_texture(float4 dir, __constant t_image *data, __global float4 *image, t_text text)
{
	float	u;
	float	v;
	int		tmpx;
	int		tmpy;
	int		pos;
//	float4	q;

/*`	q = hitprim->startoffset;
	dir = hamilton_product(q, dir);
	q.xyz = q.xyz * -1.0f;
	dir = hamilton_product(dir, q);
*/	u = atan2(dir.z, dir.x) / (2.0f * M_PI) + 0.5f;
	v = 0.5f - asin(dir.y) / M_PI;
/*	u += hitprim->xoffset;
	v += hitprim->yoffset;
	if (u > 1.0f)
		u -= 1.0f;
	if (v > 1.0f)
		v -= 1.0f;
*/	u = min(u, 0.9999f);
	v = min(v, 0.9999f);
	tmpx = u * data->width;
	tmpy = v * data->height;
	pos = tmpx + tmpy * data->width;
	return (image[pos + text.pos]);
}

static float4	get_surface(float4 dir, __constant t_image *data, __global uchar *image)
{
	float4	tmp_color;
	float	u;
	float	v;
	int		tmpx;
	int		tmpy;
	int		pos;

	u = atan2(dir.z, dir.x) / (2.0f * M_PI) + 0.5f;
	v = 0.5f - asin(dir.y) / M_PI;
	u = min(u, 0.9999f);
	v = min(v, 0.9999f);
	tmpx = u * data->width;
	tmpy = v * data->height;
	pos = tmpx * 3 + tmpy * data->width * 3;
	tmp_color.x = (float)image[pos] / 255;
	tmp_color.y = (float)image[pos + 1] / 255;
	tmp_color.z = (float)image[pos + 2] / 255;
	tmp_color.w = 1.0f;
	return (tmp_color);
}

static void	raytrace(t_scene *scene, float4 *color, t_ray *stack, int queue, int front_ray, int back_ray)
{
	int					prim_id;
	t_obj				hitobj;
	float4				tmp_color;
	float				t;
	t_ray				ray;
	t_hit				hit;

	*color = (float4)(0.0f);
	while (queue > 0)
	{
		pop_ray(stack, &ray, &front_ray, &queue);
		tmp_color = (float4)(0.0f);
		prim_id = -1;
		t = intersect(&ray, scene, &prim_id);
		if (0.0001f < t && t < MAXRENDERDIST)
		{
			hitobj.prim = scene->prim[prim_id];
			hitobj.mat = scene->mat[hitobj.prim.mat];
			hitobj.text = scene->text[hitobj.prim.text];
			hitobj.bump = scene->bump[hitobj.prim.bump];
			tmp_color = lightning(&ray, scene, hitobj, t, &hit);
			if (hitobj.text.id > 0)
				tmp_color *= get_texture(normalize(hit.point - hitobj.prim.pos),
										scene->data, scene->image, hitobj.text);
			if (hitobj.mat.type == REFLECTIVE && ray.depth < MAX_DEPTH)
				add_reflect(ray, stack, &back_ray, &queue, hit, tmp_color);
			if (hitobj.mat.type == REFRACTIVE && ray.depth < MAX_DEPTH)
				add_refract(ray, stack, &back_ray, &queue, hit, tmp_color, hitobj);
			if (hitobj.mat.type == TRANSPARANT && ray.depth < MAX_DEPTH)
				add_transparant(ray, stack , &back_ray, &queue, hit, hitobj);
		}
		else
			tmp_color = get_surface(ray.dir, scene->sky_data, scene->sky);
		*color += (tmp_color * ray.kr);
	}
	*color = clamp(*color, 0.0f, 1.0f);
}

__kernel void	renderer(__global uchar *screen, __global t_cam *cam,
		__global t_prim *prim, __global t_material *mat,
		__global t_text *text, __global t_text *bump,
		__global t_light *light, __constant t_info *info,
		__global float4 *image, __constant t_image *data,
		__global uchar *sky, __constant t_image *sky_data,
		__global float4 *bump_image, __constant t_image *bump_data)
{
	unsigned int	work_item_id;
	int				p;
	float			x;
	float			y;
	float			tmpx;
	float			tmpy;
	float4			color;
	float4			tmpcolor;
	t_ray			ray;
	t_scene			scene;
	t_ray			stack[MAX_RAY_COUNT];
	int				queue;
	int				front_ray;
	int				back_ray;

	work_item_id = get_global_id(0);
	x = work_item_id % WIDTH;
	y = work_item_id / WIDTH;
	if (x < WIDTH && y < HEIGHT)
	{
		tmpx = x;
		tmpy = y;
		p = 0;
		scene = init_scene(cam, prim, mat, text, bump, light, info, image, data,
							sky, sky_data, bump_image, bump_data);
		color = (float4)(0.0f);
		while (tmpy < y + 1.0f)
		{
			queue = 0;
			front_ray = 0;
			back_ray = 0;
			current_ray(tmpx, tmpy, scene.cam, &ray);
			push_ray(stack, ray, &back_ray, &queue);
			raytrace(&scene, &tmpcolor, stack, queue, front_ray, back_ray);
			color += tmpcolor;
			tmpx = tmpx + 1.0f / scene.info->aa;
			p += 1;
			if (tmpx >= x + 1.0f)
			{
				tmpx = x;
				tmpy = tmpy + 1.0f / scene.info->aa;
			}
		}
		color = color / p;
		work_item_id = work_item_id * 4;
		screen[work_item_id] = color.z * 255;
		screen[work_item_id + 1] = color.y * 255;
		screen[work_item_id + 2] = color.x * 255;
		screen[work_item_id + 3] = 255;
	}
}
