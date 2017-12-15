#include "rt.cl.h"

static float	chiggx(float v)
{
	return (v > 0 ? 1 : 0);
}

static float	ggx_distribution(float4 dir, float4 normal, float4 halfv, float alpha)
{
	float	ndoth;
	float	alpha2;
	float	ndoth2;
	float	den;

	ndoth = dot(normal, halfv);
	alpha2 = alpha * alpha;
//	alpha2 = alpha2 * alpha2;
	ndoth2 = ndoth * ndoth;
	den = ndoth2 * alpha2 + (1 - ndoth2);
	return ((chiggx(ndoth) * alpha2) / (den * den * M_PI));
}

static float	ggx_partialgeometryterm(float4 dir, float4 normal, float4 halfv, float alpha)
{
	float	vdoth2;
	float	chi;
	float	tan2;

	alpha = alpha * alpha;
	vdoth2 = clamp(dot(dir, halfv), 0.001f, 1.0f);
	chi = chiggx(vdoth2 / clamp(dot(dir, normal), 0.001f, 1.0f));
	vdoth2 = vdoth2 * vdoth2;
	tan2 = (1 - vdoth2) / vdoth2;
	return ((chi * 2) / (1 + sqrt(1 + alpha * alpha * tan2)));

}

static float4	dielectric_fresnel_schlick(float4 dir, float4 halfv, float4 f0)
{
	float	cost;

	cost = dot(dir, halfv);
	return (f0 + (1 - f0) * pow(1 - cost, 5));
}

static float4	conductor_fresnel_schlick(float4 dir, float4 halfv, float ior, float k)
{
	float	cost;

	cost = dot(dir, halfv);
	return (((ior - 1) * (ior - 1) + 4 * ior * pow(1 - cost, 5) + k * k) / ((ior + 1) * (ior + 1) + (k * k)));
}

float4	bumpmap(float4 light_dir, float4 n);

static float4	specular(t_hit hit, float4 light_dir, t_obj hitobj, float4 intensity, float cos_theta, float4 *ks)
{
	float4	tdir;
	float4	halfv;
	float4	fresnel;
	float	distribution;
	float	view_geometry;
	float	light_geometry;
	float	denominator;
	float	nov;
	float	noi;
	float4	f0;

	f0 = (float4)(1.0f - hitobj.mat.coef) / (1.0f + hitobj.mat.coef);
	f0 = f0 * f0;
	f0 = mix(f0, hitobj.prim.color, (float)1.0f);
	if (hitobj.bump.id > 0)
		tdir = bumpmap(hit.ray_origin.dir, normalize(hit.point - hitobj.prim.pos)) * -1.0f;
	else
		tdir = hit.ray_origin.dir * -1.0f;
	halfv = normalize(tdir + light_dir);
	distribution = ggx_distribution(light_dir, hit.normal, halfv, hitobj.mat.roughness);
	view_geometry = ggx_partialgeometryterm(tdir, hit.normal, halfv, hitobj.mat.roughness);
	light_geometry = ggx_partialgeometryterm(light_dir, hit.normal, halfv, hitobj.mat.roughness);
	fresnel = dielectric_fresnel_schlick(tdir, halfv, f0);
	nov = max(dot(hit.normal, tdir), 0.0f);
	noi = max(dot(hit.normal, halfv), 0.0f);
	denominator = clamp(4.0f * (nov * noi + 0.05f), 0.0f, 1.0f);
	*ks += fresnel;
	return ((((float4)distribution *  fresnel * view_geometry * light_geometry) / denominator) * intensity * cos_theta);
}

