#include "rt.cl.h"

static float4	hamilton_product(float4 v, float4 w)
{
	float4	r;

	r.w = v.w * w.w - v.x * w.x - v.y * w.y - v.z * w.z;
	r.x = v.w * w.x + v.x * w.w + v.y * w.z - v.z * w.y;
	r.y = v.w * w.y - v.x * w.z + v.y * w.w + v.z * w.x;
	r.z = v.w * w.z + v.x * w.y - v.y * w.x + v.z * w.w;

	return (r);
}
