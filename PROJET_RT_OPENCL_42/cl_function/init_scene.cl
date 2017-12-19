#include "rt.cl.h"

static t_scene	init_scene(__global t_cam *cam,
		__global t_prim *prim, __global t_material *mat,
		__global t_text *text, __global t_text *bump,
		__global t_light *light, __constant t_info *info,
		__global float4 *image, __constant t_image *data,
		__global uchar *sky, __constant t_image *sky_data,
		__global float4 *bump_image, __constant t_image *bump_data)
{

	t_scene	scene;

	scene.cam = cam;
	scene.prim = prim;
	scene.mat = mat;
	scene.text = text;
	scene.bump = bump;
	scene.light = light;
	scene.image = image;
	scene.info = info;
	scene.data = data;
	scene.sky = sky;
	scene.sky_data = sky_data;
	scene.bump_image = bump_image;
	scene.bump_data = bump_data;
	return (scene);
}
