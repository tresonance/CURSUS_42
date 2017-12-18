#ifndef RT_CL_H
# define RT_CL_H

#define WIDTH 800
#define HEIGHT 600

#define FOC 1.0

#define MAXRENDERDIST 8000.0f

#define SPHERE 0
#define PLANE 1
#define CONE 2
#define CYLINDER 3
#define BOX 4
#define SKY 5
#define TRIANGLE 6
#define PARABOLOID 7
#define TORE 8

#define PARRALEL 0
#define POINT 1

#define MAX_DEPTH 3
#define MAX_RAY_COUNT 8

#define DIFFUSE 0
#define REFLECTIVE 1
#define REFRACTIVE 2
#define TRANSPARANT 3

#define TOLERANCE 1.0e-6
#define INFINI 1.0e20

typedef struct	s_image
{
	int			width;
	int			height;
}				t_image;

typedef struct	s_prim
{
	int			type;
	float4		pos;
	float4		pos1;
	float4		pos2;
	float4		color;
	float4		rot;
	float		size;
	int			mat;
	int			text;
	int			bump;
}				t_prim;

typedef struct	s_material
{
	int			type;
	float		roughness;
	float		coef;
}				t_material;

typedef struct	s_text
{
	int			id;
	int			pos;
	float		xoffset;
	float		yoffset;
	float4		startoffset;
}				t_text;

typedef struct	s_bump
{
	int			pos;
	float		xoffset;
	float		yoffset;
	float4		startoffset;
}				t_bump;

typedef struct	s_obj
{
	t_prim		prim;
	t_material	mat;
	t_text		text;
	t_text		bump;
}				t_obj;

typedef struct	s_light
{
	float4		pos;
	float4		dir;
	float4		color;
	float		intensity;
	int			type;
}				t_light;

typedef struct	s_ray
{
	float4		pos;
	float4		dir;
	int			depth;
	float4		kr;
	float4		color;
}				t_ray;

typedef struct	s_hit
{
	t_ray		ray_origin;
	float4		point;
	float4		normal;
	float		t;
}				t_hit;

typedef struct	s_cam
{
	float4		pos;
	float4		dir;
	float4		lookat;
	float4		normal;
	float4		right;
	float4		up;
}				t_cam;

typedef struct	s_info
{
	int			nb_prim;
	int			nb_light;
	int			nb_text;
	int			nb_mat;
	int			nb_bump;
	int			aa;
}				t_info;

typedef struct	s_scene
{
	__global t_cam		*cam;
	__global t_prim		*prim;
	__global t_material	*mat;
	__global t_text		*text;
	__global t_text		*bump;
	__global t_light	*light;
	__constant t_info	*info;
	__global float4		*image;
	__constant t_image	*data;
	__global uchar		*sky;
	__constant t_image	*sky_data;
	__global float4		*bump_image;
	__constant t_image	*bump_data;
}				t_scene;

typedef struct s_poly
{
	float a;
	float b;
	float c;
	float d;
	float e;
	float p;
	float q;
	float r;
	float u;
	float v;
	float t;
	float s;
	float delta;
}					t_poly;

#include "init_scene.cl"
#include "ray.cl"
#include "inter.cl"
#include "specular.cl"
#include "reflect.cl"
#include "refract.cl"
#include "transparant.cl"
#include "vector.cl"

void	push_ray(t_ray *stack, t_ray ray, int *current, int *queue);
void	pop_ray(t_ray *stack, t_ray *ray, int *current, int *queue);
void	current_ray(float x, float y, __global t_cam *cam, t_ray *ray);

float	sphere_inter(t_prim prim, t_ray *ray, int flag);
float	cylinder_inter(t_prim prim, t_ray *ray);
float	cone_inter(t_prim prim, t_ray *ray);
float	plane_inter(t_prim prim, t_ray *ray);
float	triangle_inter(t_prim prim, t_ray *ray);
float	box_inter(t_prim prim, t_ray *ray);
float	intersect(t_ray *ray, t_scene *scene, int *prim_id);

float4	specular(t_hit hit, float4 light_dir, t_obj hitobj,
		float4 intensity, float cos_theta, float4 *ks);

void	reflect(t_ray *ray, t_hit hit);
int		refract(t_ray *ray, t_hit hit, float ior);
float	fresnel(t_hit hit, float ior);

void	add_reflect(t_ray ray, t_ray *stack, int *back_ray, int *queue,
		t_hit hit, float4 tmp_color);
void	add_refract(t_ray ray, t_ray *stack, int *back_ray, int *queue,
		t_hit hit, float4 tmp_color, t_obj hitobj);
void	add_transparant(t_ray ray, t_ray *stack, int *back_ray, int *queue,
		t_hit hit, t_obj hitobj);

#endif
