
#include "rt.h"

unsigned char perm(int x,  int y,  int z)
{
	const unsigned char p[512] = {
		151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225,
		140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247,
		120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 
		33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165,
		71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211,
		133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63,
		161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135,
		130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226,
		250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59,
		227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152,
		2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253,
		19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
		251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235,
		249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176,
		115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29,
		24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180, 151, 160, 137, 91,
		90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 127, 4, 150, 254,
		138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66,
		215, 61, 156, 180};
	return (p[z + p[y + p[x]]]);
}

int *get_grad(int x,  int y,  int z)
{
	int rand_value;
	static int _grad3[16][3] = {
		{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, 
		{1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1}, 
		{0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}, 
		{1, 1, 0}, {-1, 1, 0}, {0, -1, 1}, {0, -1, -1}};
	rand_value = perm(x,  y,  z);;
	return _grad3[rand_value & 15];
}

double fast_dot(const int *v, const double x, const double y, const double z)
{
	return v[0] * x + v[1] * y + v[2] * z;
}

//Calcule simplement la valeur de ce polynôme en x=t
double quintic_poly(const double t)
{
	const double t3 = t * t * t;
	return t3 * (t * (t * 6.0 - 15.0) + 10.0);
}

//  //Fonction : Sépare la partie entière et fractionnaire
void int_and_frac(double value, int *integer_part, double *fractional_part)
{
	*integer_part = (int)value;
	if(value < 0.0f)
		*integer_part -= 1;
	*fractional_part = value - (*integer_part);
}

//La fonction principale, permettant d'obtenir le bruit lissé
double smooth_noise_3d(double x_pos, double y_pos, double z_pos)
{
	//Les parties entières
	int X, Y, Z;
	//Les parties fractionnaires
	double x, y, z;
	//Comme pour le précédent algorithme, nous séparons parties entière et fractionnaire.
	int_and_frac(x_pos, &X, &x);
	int_and_frac(y_pos, &Y, &y);
	int_and_frac(z_pos, &Z, &z);
	//Nous appliquons un modulo 256, de façon à ce que ces valeurs soient comprises dans 
	//notre table de permutation,et que nous puissions utiliser la fonction d'obtention
	//de gradient.
	X &= 255;
	Y &= 255;
	Z &= 255;
	const double g000 = fast_dot(get_grad(X, Y, Z), x, y, z);
	const double g001 = fast_dot(get_grad(X, Y, Z + 1), x, y, z - 1.);
	const double g010 = fast_dot(get_grad(X, Y + 1, Z), x, y - 1., z);
	const double g011 = fast_dot(get_grad(X, Y + 1, Z + 1), x, y - 1., z - 1.);
	const double g100 = fast_dot(get_grad(X + 1, Y, Z), x - 1., y, z);
	const double g101 = fast_dot(get_grad(X + 1, Y, Z + 1), x - 1., y, z - 1.);
	const double g110 = fast_dot(get_grad(X + 1, Y + 1, Z), x - 1., y - 1., z);
	const double g111 = fast_dot(get_grad(X + 1, Y + 1, Z + 1), x - 1., y - 1., z - 1.);

	const double u = quintic_poly(x);
	const double v = quintic_poly(y);
	const double w = quintic_poly(z);
	
	const double x00 = linear_interpolate(g000 , g100, u);
	const double x10 = linear_interpolate(g010 , g110, u);
	const double x01 = linear_interpolate(g001 , g101, u);
	const double x11 = linear_interpolate(g011 , g111, u);
	const double xy0 = linear_interpolate(x00 , x10, v);

	const double xy1 = linear_interpolate(x01 , x11, v);
	const double xyz = linear_interpolate(xy0 , xy1, w);
	return xyz;
}

t_color		perlin_color(t_hit *inter, t_env *e)
{
	double noise;
	t_color col;

	col = calculate_matte(inter, e);
	noise = smooth_noise_3d(inter->point.x, inter->point.y, inter->point.z);
	return((t_color){noise * col.r , noise * col.g , noise * col.b  });
}
