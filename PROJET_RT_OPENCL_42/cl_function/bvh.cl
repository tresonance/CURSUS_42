#define WIDTH 900
#define HEIGHT 900
#define FOC 1.0
#define MAXRENDERDIST 8000.0f
#define SPHERE 0
#define PLANE 1
#define CONE 2
#define CYLINDER 3
#define PARRALEL 0
#define POINT 1
#define MAX_DEPTH 3
#define MAX_RAY_COUNT 8
#define DIFFUSE 0
#define REFRACTIVE 1
#define REFLECTIVE 2
#define PMIN (float4)(-500.0f, -500.0f, -500.0f, 1.0f)
#define PMAX (float4)(500.0f, 500.0f, 500.0f, 1.0f)
#define MIN -500.0f
#define MAX 500.0f

typedef struct	s_aabb
{
	float4		min;
	float4		max;

}				t_aabb;

typedef struct	s_bvh
{
	float4		min;
	float4		max;
	uint		count;
	int			obj_id;
	uint		codes;
	uint		parent;
	uint		childa;
	uint		childb;
}				t_bvh;

typedef struct	s_obj
{
	int			type;
	float4		pos;
	float4		color;
	float4		rot;
	float		size;
	float		roughness;
	int			reflective;
	int			refractive;
}				t_obj;

uint			expandbits(uint v)
{
	v = (v * 0x00010001u) & 0xFF0000FFu;
	v = (v * 0x00000101u) & 0x0F00F00Fu;
	v = (v * 0x00000011u) & 0xC30C30C3u;
	v = (v * 0x00000005u) & 0x49249249u;
	return (v);
}

uint			morton3d(float4 v)
{
	uint	xx;
	uint	yy;
	uint	zz;

	v.x = min(max(v.x * 1024.0f, 0.0f), 1023.0f);
	v.y = min(max(v.y * 1024.0f, 0.0f), 1023.0f);
	v.z = min(max(v.z * 1024.0f, 0.0f), 1023.0f);
	xx = expandbits((uint)v.x);
	yy = expandbits((uint)v.y);
	zz = expandbits((uint)v.z);
	return (xx * 4 + yy * 2 + zz);
}

float4	get_lbb(t_obj obj, int type)
{
	if (type == MIN)
		if (obj.type == SPHERE)
			return (obj.pos - obj.size);
	if (obj.type == SPHERE)
		return (obj.pos + obj.size);
}

void	get_ibb(__global t_bvh *bvh, uint current)
{
	float4	min;
	float4	max;

	min = bvh[bvh[current].childa].min;
	max = bvh[bvh[current].childb].min;
	bvh[current].min = min(min, max);
	min = bvh[bvh[current].childa].max;
	max = bvh[bvh[current].childb].max;
	bvh[current].max = max(min, max);
}

int2			determine_range(__global uint *codes, __constant int *nb_obj,
		uint global_id)
{
	uint	tmpindex;
	uint2	length;
	int2	range;
	int		new_test;
	int		dir;
	int		div;
	int		l;
	int		t;
	uint	d_min;
	int		l_max;
	int		test_index;
	int		last_index;
	uint	splitprefix;
	uint	current;
	uint	plusone;
	uint	minone;

	if (global_id == 0)
		return ((int2)(0, *nb_obj - 1));
	last_index = *nb_obj - 1;
	current = codes[global_id];
	plusone = codes[global_id + 1];
	minone = codes[global_id - 1];
	tmpindex = global_id;
	if (minone == current && current == plusone)
	{
		while (tmpindex > 0 && tmpindex < (uint)(*nb_obj - 1))
		{
			tmpindex += 1;
			if (tmpindex >=  (uint)(*nb_obj - 1) || codes[tmpindex] != codes[tmpindex + 1])
				break;
		}
		return ((int2)(global_id, tmpindex));
	}
	else
	{
		length = (uint2)(clz(current ^ plusone), clz(current ^ minone));
		dir = sign((float)length.x - (float)length.y);
		d_min = length[dir > 0];
	}
	l_max = 2;
	test_index = global_id + l_max * dir;
	while (test_index <= last_index && test_index >= 0 &&
			clz((current ^ codes[test_index]) > d_min))
	{
		l_max = l_max << 1;
		test_index = global_id + l_max * dir;
	}
	l = 0;
	div = 2;
	while (l_max / div >= 1)
	{
		t = l_max / div;
		new_test = global_id + (l + t) * dir;
		if (new_test <= last_index && new_test >= 0)
		{
			splitprefix = clz(current ^ codes[new_test]);
			if (splitprefix > d_min)
				l = l + t;
		}
		div = div << 1;
	}
	range.x = min(global_id, global_id + l * dir);
	range.y = max(global_id, global_id + l * dir);
	return (range);
}

int				find_split(__global uint *codes, int2 range)
{
	uint	first;
	uint	last;
	uint	splitcode;
	uint	commonprefix;
	uint	split;
	int		step;
	uint	newsplit;
	uint	splitprefix;

	first = codes[range.x];
	last = codes[range.y];
	commonprefix = clz(first ^ last);
	split = first;
	step = last - first;
	while (step > 1)
	{
		step = (step + 1) >> 1;
		newsplit = split + step;
		if (newsplit < last)
		{
			splitcode = codes[newsplit];
			splitprefix = clz(first ^ splitcode);
			if (splitprefix > commonprefix)
				split = newsplit;
		}
	}
	return (split);
}

__kernel void init_codes(__global t_obj *obj, __constant int *sorted_obj_id,
		__global uint *codes, __constant int *nb_obj)
{
	uint	global_id;
	float4	code_norm;

	global_id = get_global_id(0);
	code_norm = (obj[global_id].pos - PMIN) / (PMAX - PMIN);
	if (obj[global_id].type == SPHERE)
		codes[global_id] = morton3d(code_norm);
}

__kernel void init_obj(__global t_obj *obj, __constant int *sorted_obj_id,
		__global uint *codes,
		__constant int *nb_obj, __global t_bvh *bvh)
{
	uint	global_id;

	global_id = get_global_id(0);
	bvh[global_id].count = 0;
	bvh[global_id].min = get_lbb(obj[sorted_obj_id[global_id]], MIN);
	bvh[global_id].max = get_lbb(obj[sorted_obj_id[global_id]], MAX);
	bvh[global_id].obj_id = sorted_obj_id[global_id];
	bvh[global_id].childa = UINT_MAX;
	bvh[global_id].childb = UINT_MAX;
	bvh[global_id].parent = 0;
	bvh[global_id].codes = codes[sorted_obj_id[global_id]];
}

__kernel void init_bvh(__global t_obj *obj, __global uint *codes,
		__constant int *nb_obj, __global t_bvh *bvh)
{
	uint	global_id;
	int2	range;
	int		split;
	bool	isleaf;
	uint	childa;
	uint	childb;

	global_id = get_global_id(0);
	range = determine_range(codes, nb_obj, global_id);
	split = find_split(codes, range);
	global_id += *nb_obj;
	if (global_id == *nb_obj)
		bvh[global_id].parent = UINT_MAX;
	isleaf = split == range.x;
	childa = split + *nb_obj * !isleaf;
	isleaf = split + 1 == range.y;
	childb = split + 1 + *nb_obj * !isleaf;
	bvh[global_id].count = 0;
	bvh[global_id].childa = childa;
	bvh[global_id].childb = childb;
	bvh[childa].parent = global_id;
	bvh[childb].parent = global_id;
}

__kernel void compute_bb(__global t_bvh *bvh, __global volatile uint *counters,
		__constant int *nb_obj)
{
	uint	current;

	current = bvh[get_global_id(0)].parent;
	while (current != UINT_MAX)
	{
		atomic_inc(counters + (current - *nb_obj));
		if (*(counters + (current - *nb_obj)) > 1)
		{
			get_ibb(bvh, current);
			current = bvh[current].parent;
		}
		else
			current = UINT_MAX;
	}
}
