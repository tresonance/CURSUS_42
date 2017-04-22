/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 10:54:17 by ibtraore          #+#    #+#             */
/*   Updated: 2017/04/21 04:04:51 by thchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_H
# define RTV_H

# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>

# define ESCAPE 53
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define PLUS 69
# define MINUS 78
# define EIGHT 91
# define TWO 84
# define FOUR 86
# define SIX 88
# define A 0
# define D 2
# define R 15
# define S 1
# define W 13
# define LEFT 123
# define RIGHT 124
# define C 8
# define Q 12
# define E 14
# define V 9
# define TRUE 1
# define FALSE 0
# define FOC 2.0
# define WIDTH 800
# define HEIGHT 800

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
	double				w;
}						t_vector;

typedef struct			s_matrix
{
	double m[4][4];
}						t_matrix;

typedef struct			s_color
{
	uint8_t				r;
	uint8_t				g;
	uint8_t				b;
}						t_color;

typedef struct			s_cam
{
	t_vector			pos;
	t_vector			dir;
	t_vector			normal;
	t_vector			right;
	t_vector			up;
}						t_cam;

typedef struct			s_ray
{
	t_vector			pos;
	t_vector			dir;
}						t_ray;

typedef struct			s_solver
{
	t_vector			dist;
	double				a;
	double				b;
	double				c;
	double				delta;
	double				t1;
	double				t2;
}						t_solver;

typedef struct			s_obj
{
	char				*name;
	t_vector			pos;
	t_color				color;
	t_vector			rot;
	double				size;
	double				ambient;
	double				diffuse;
	double				specular;
	int					current;
}						t_obj;

typedef struct			s_img
{
	int					endian;
	int					size_line;
	char				*img_ptr;
	int					bpp;
}						t_img;

typedef struct			s_hit
{
	t_ray				*ray_origin;
	t_vector			point;
	t_vector			normal;
	t_color				color;
	double				t;
}						t_hit;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data;
	int					size_line;
	int					endian;
	int					bpp;
}						t_mlx;

typedef struct			s_env
{
	t_mlx				mlx;
	t_cam				cam;
	t_list				*obj;
	t_vector			up;
	double				aa;
	double				t;
	double				p;
}						t_env;

t_color					get_color(int color);
t_color					get_hit_color(t_list *list, t_obj *light, t_obj *obj,
										t_hit t);
void					get_hit_point_info(t_hit *hit_point, t_obj *obj,
											t_ray *ray);
int						shadow_or_not(t_list *lst, t_obj *obj, t_env *e);
t_obj					*closest_obj_intercepted(t_list *lst, t_ray *ray,
												t_env *e);

double					sphere_inter(t_obj *obj, t_ray *ray);
double					cylinder_inter(t_obj *obj, t_ray *ray);
double					cone_inter(t_obj *obj, t_ray *ray);
double					plane_inter(t_obj *obj, t_ray *ray);

t_list					*check_obj(t_list *lst, char *name);
void					draw_obj(t_env *e);
void					pixel_put(int x, int y, t_color col, t_mlx mlx);
void					err_exit(char *str);

int						parser_obj(t_list **obj, char **tab, int i);
int						parser_cam(t_cam *cam, char **tab);

void					lst_add_back(t_list **lst, t_list *new);
void					initialize_tab(int *tab, int n);

float					normevect(t_vector *v1);
t_vector				crossvect(t_vector *v1, t_vector *v2);
t_vector				scalevect(double k, t_vector *v1);
t_vector				subvect(t_vector *v1, t_vector *v2);
t_vector				addvect(t_vector *v1, t_vector *v2);
void					normalize(t_vector *v);
double					prodscal(t_vector *v1, t_vector *v2);
t_vector				opposite(t_vector *v);

void					current_ray(double x, double y, t_env *e, t_ray *ray);
t_color					ft_color(t_obj *hit_obj);
t_color					lighting(t_list *lst, t_obj **obj, t_ray ray, double t);
double					solver(t_solver *s);

int						check_param(char *str, int i, int max);
int						get_col(t_obj *obj, char **tab, int *i);
int						get_pos(t_obj *obj, char **tab, int *i);
int						get_size(t_obj *obj, char **tab, int *i);
int						get_rot(t_obj *obj, char **tab, int *i);
int						get_light_info(t_obj *obj, char **tab, int *i);

int						get_scene(t_list **obj, t_cam *cam, char *file);

int						parser(t_list **obj, t_cam *cam, char **tab);

double					find_closest_t(t_list *list, t_ray *ray,
										t_obj **hit_obj);

void					copy_cam(t_cam *dst, t_cam src);
int						copy_list(t_list **dst, t_list *src);
void					copy_up(t_vector *dst, t_vector src);

t_matrix				translate_matrix(t_vector dir);
t_matrix				rotate_matrix(t_vector dir, double angle);
t_vector				matrix_mul_vect(t_matrix m, t_vector v);
t_matrix				identity_matrix(void);
int						key_hook(int key, t_env *e);
double					ft_clamp(double value, int a, int b);
void					clear_env(t_env *env);

void					translate(int key, t_env *e);
void					rotate(int key, t_env *e);
void					rotate_n_axis(int key, t_env *e);
#endif
