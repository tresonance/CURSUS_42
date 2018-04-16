/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 10:54:17 by ibtraore          #+#    #+#             */
/*   Updated: 2017/05/13 11:30:38 by ibtraore         ###   ########.fr       */
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
# define MAX_LIGHT 10
# define ONE 0
# define TWO 6
# define FOUR 12
# define FIVE 1
# define SEVEN 13
# define EIGHT 7

# define Q 12
# define W 13
# define E 14
# define D 2
# define A 0
# define S 1

# define I 34
# define O 31
# define U 32
# define J 38
# define K 40
# define L 37

# define R 15
# define C 8
# define V 9
# define B 11
# define O 31
# define TRUE 1
# define FALSE 0
# define FOC 2.0
# define WIDTH 500
# define HEIGHT 500

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
	t_vector			lookat;
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

typedef struct			s_light
{
	t_vector			pos;
	t_color				col;
	struct s_light		*next;
}						t_light;

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
	t_cam				*cam;
	t_list				*obj;
	t_vector			up;
	double				aa;
	double				t;
	double				p;
	char				*itoapos;
	char				*itoasize;
	char				*itoarot;
	char				*itoacampos;
	char				*itoacamdir;
	t_obj				*hit_obj;
	int					is_obj_selected;
	t_obj				*light[MAX_LIGHT];
	int					total_light;
}						t_env;

void					display_info1(t_env *e, t_obj *obj);
void					display_info2(t_env *e, t_obj *obj);
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
void					pixel_put(int x, int y, t_color col, t_mlx *mlx);
void					err_exit(char *str);

int						parser_obj(t_list **obj, char **tab, int i);
int						parser_cam(t_cam *cam, char **tab);

void					lst_add_back(t_list **lst, t_list *news);
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

int						search_inside(t_obj *obj);

int						check_param(char *str, int i, int max);
int						get_col(t_obj *obj, char **tab, int *i);
int						get_pos(t_obj *obj, char **tab, int *i);
int						get_size(t_obj *obj, char **tab, int *i);
int						get_rot(t_obj *obj, char **tab, int *i);
int						get_light_info(t_obj *obj, char **tab, int *i);
int						get_obj(t_list **obj, char **tab, int *i);

int						get_scene(t_list **obj, t_cam *cam, char *file);

int						parser(t_list **obj, t_cam *cam, char **tab);

double					find_closest_t(t_list *list, t_ray *ray,
										t_obj **hit_obj);

void					copy_cam(t_cam *dst, t_cam src);
int						copy_list(t_list **dst, t_list *src);
void					copy_up(t_vector *dst, t_vector src);
void					convert_list_into_struct(t_env *e);
t_env					*init_env(void);

int						expose_hook_func(t_env *e);
int						mouse_hook_func(int button, int x, int y, t_env *e);
int						key_hook_func(int key, t_env *e);
int						close_hook_func(int key, t_env *e);
int						close_win(t_env *e);
double					ft_clamp(double value, int a, int b);
void					clear_env(t_env **env);

void					translate(int key, t_env *e);
void					translate_light(int key, t_vector r, t_vector n,
						t_env *e);
void					rotate_camera(int key, t_env *e);
int						clicked_obj_info(int x, int y, t_env *e);
void					display_cam_info(t_env *e);
void					create_light_array(t_env *e);

void					light_position(t_env *e);
#endif
