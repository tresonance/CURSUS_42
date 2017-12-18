/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 00:12:27 by ibtraore          #+#    #+#             */
/*   Updated: 2017/09/20 15:45:33 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
#define RT_H

#include "../libft/includes/libft.h"
#include <stdint.h>
#include <fcntl.h>
#include <math.h>
#include "../minilibx_macos/mlx.h"
#include <pthread.h>
#define PI 3.14159265358979323846264338327950288419716939937511
#define FOC 1.0
#define MIN(a, b)  (((a) <= b) ? a : b)
#define MAX(a, b)  (((a) >= b) ? a : b)

#define WIDTH 600
#define HEIGHT 600

#define EPSILON 1.0e-6  //INTERSECTION
#define TOLERANCE 1.0e-8 //ALGEBRA
#define INFINI 8000.0
#define DIRECTE 0
#define PARALLELE 1

#define BIAS 0.0001
#define MIN_COLOR_INTENSITY 0.001
#define MAX_DEPTH 5
#define MAX_DIST 8000
#define TRUE 1
#define FALSE 0
#define PRIMARY_RAY 0
#define REFLECTION_RAY 1
#define REFRACTION_RAY 2

#define REFRACTION_VACUUM    1.0000

// Range of allowed refraction values...
#define INDICE_MINIMUM  1.0000
#define INDICE_MAXIMUM  9.0000
#define UNION 3
#define INTERSECTION 1
#define DIFFERENCE 2

# define THREADS 9
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define PLUS 69
# define MINUS 78

# define ONE 83
# define TWO 84
# define FOUR 86
# define FIVE 87
# define SEVEN 89
# define EIGHT 91

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


typedef struct   s_vector
{
                double x;
                double y;
				double z;
}				t_vector;

typedef struct 	s_color
{
		double r;
		double g;
		double b;
}		t_color;

typedef struct s_pixel
{
		t_color color;
		int is_ambiguous;
}		t_pixel;

typedef struct s_polyn
{
	float a;
	float b;
	float c;
	float d;
	float e;

	double p;
	double q;
	double r;
	double delta;

	double s;
	double t;
	double u; 
	double v;
}				t_polyn;

typedef struct s_base
{
		t_vector rdir;
		t_vector sdir;
		t_vector tdir;
}		t_base;

typedef struct s_cam
{
        	t_vector pos;
        	t_vector lookat;

        	t_vector dir;
        	t_vector right;
        	t_vector up;
}				t_cam;

typedef struct	s_obj
{
		/*cuboid*/
		double a;
		double b;
		double c;

		/*cylinder*/
		double zdisk;
		double radius;
		int		cut_flag;
		t_vector cut_point;
		t_vector cut_axe;
		int		num_cut_plane;;
		/*thinring*/
		/*        */
		
		int obj_index;;
		t_vector axe;
		char *name;
		
		/*chessbord*/
		double inner_size;
		double xborder_size;
		double yborder_size;

		/*triangle*/
		t_vector v0;
		t_vector v1;
		t_vector v2;
		t_color v1color;
		t_color v2color;
		int	degrade;
		
		int enclosed;
		t_vector center;
		int is_light_obj;
		t_base base;

		t_color matte;
		t_color glossy;
		
		double matte_factor;
		double glossy_factor;
		double specular_factor;
		int type[2];
		int tag;
		int parallel;
		int left;
		int	right;
		int	up;
		int	down;
		int	front;
		int	back;

		double refractive_index;
		struct s_obj *next;

		double tmin;
		double tmax;
		int csg_operator;
		t_vector  min_pos;
		t_vector  max_pos;
}		t_obj;

typedef struct	s_ray
{
		t_vector pos;
		t_vector dir;
		int type;
		t_obj *obj_from;
}		t_ray;


typedef struct s_hit
{
		double t;
		double displacement;
		t_vector point;
		t_vector normal;
		t_ray in_ray;
		t_obj *obj;
		char tag[20];
		t_vector ray_origin;
		struct s_hit *next;
}		t_hit;

typedef struct s_light
{
		t_vector pos;
		t_color color;
		int		parallel;
		struct s_light *next;
}		t_light;

typedef struct s_light_obj
{
		t_obj *obj;
		struct s_light_obj *next;
}		t_light_obj;

typedef struct s_aabb
{
	t_vector min;
	t_vector max;
}				t_aabb;

typedef struct s_scene
{
	t_obj *obj;
	t_light *light;
	t_light_obj *light_obj;
	double ambient_refractive_index;
	t_color ray_intensity;
	t_color background;
	t_aabb	aabb;
}		t_scene;

typedef struct s_texture
{
	void *image;
	char *imgptr;
	int endian;
	int sl;
	int bpp;
	int width;
	int height;
	int x; 
	int y;
}		t_texture;


typedef struct s_thread_arg
{
	int id;
	t_color color;
	t_ray ray;
	int depth;
	//pthread_mutex_t lock_x;
	//pthread_attr_t attr;
	struct s_env  *mlx;
}				t_thread_arg;

typedef struct s_thread
{
	pthread_t thread;
	pthread_attr_t attr;
	t_thread_arg arg;
	struct s_thread  *next;
	//pthread_mutex_t lock_x;
}				t_thread;


typedef struct	s_env
{
	void *mlx;
	void *win;
	void *img;

	char *data;
	int sl;
	int endian;
	int bpp;

	t_cam *cam;
	t_hit *hit_list;

	t_scene *scene;
	
	/*texture*/	
	//int argc;
	//char *scene_file;
	t_texture **texture_arr;
	int total_texture;

	t_pixel *pixel;
	double zoom;

	/*to delete */
	double kr;
	double kt;
	//double ratio;
	float cos_i;
	float cos_t;
	float sin_i;
	float sin_t;
	double etai;
	double etat;
	t_ray	refl;
	t_ray	refr;
	t_color reflcolor;

	t_color refrcolor;	

	int  aa;
	t_vector up;
	char	*itoacampos;
	char	*itoacamdir;
	char	*itoapos;
	t_obj	*hit_obj;
	char	*itoaaxe;
	char	*itoasize;
	int		is_obj_selected;
	double trans_speed;
	double rot_speed;

	t_color color;

	pthread_mutex_t lock_x;
	//pthread_attr_t attr;
	pthread_cond_t cond;

	struct s_thread *thread_array;
	int num_thread;
	//struct s_thread *main_thread;
	struct s_thread_arg arg;
	//void*stack;
	
	float dx;
	float flagdx;
	float dy;
	float flagdy;
	float flag;
}		t_env;

typedef struct s_kdtree
{
	t_aabb		*aabb;
	int			axis;
	int			is_leaf;
	struct s_kdtree *left;
	struct s_kdtree *right;
}				t_kdtree;

/*typedef struct s_thread_arg
{
	int id;
	t_color color;
	t_ray ray;
	int depth;
	//pthread_mutex_t lock_x;
	//pthread_attr_t attr;
	t_env *mlx;
}				t_thread_arg;

typedef struct s_thread
{
	pthread_t thread;
	pthread_attr_t attr;
	t_thread_arg arg;
	struct s_thread  *next;
	//pthread_mutex_t lock_x;
}				t_thread;*/

typedef t_color (*ptr_f)(t_hit*, t_env*);
/*********************** FUNCTIONS *********************/

/*
 *vector.c
 */

t_vector		subvect(t_vector u, t_vector v);
t_vector		addvect(t_vector u, t_vector v);
void			opposite(t_vector *v);
t_vector		scalevect(double a, t_vector v);
double			prodscal(t_vector u, t_vector v);
t_vector		crossvect(t_vector u, t_vector v);
double			normevect(t_vector u);
double			normevectsquar(t_vector v);
void			normalize(t_vector *v);
t_vector		add_bias(double bias, t_vector v);
int			isnull_vector(t_vector v);

/*
 *algebre.c
 */
int			second_degre(double coef[], double result[]);

/*
 *quadratic_solver.c
 */
int			quadratic(t_polyn poly , double  roots[]);
double			cut_obj(double *coef , t_obj *obj, t_vector rdir, t_vector rpos);

/*
 *cubic_solver.c
 */
int				cubic(t_polyn poly, double  roots[]);


/*
 *quartic_solver.c
 */
int                     quartic(t_polyn poly, double  roots[]);

/*
 * list_remove_if
 */
void		ft_remove_if(t_obj **begin_list);

/*
 *read_file.c
 */
//int			get_scene(t_obj **obj, t_cam *cam, char *file);;
int			scene(char *file, t_cam **cam, t_obj **obj, t_light **light_point, t_light_obj **light_obj);


/*
 *store_camera_data.c
 */
int			check_param(char *str, int i, int max);
int			parser_cam(t_cam *cam, char **tab);

/*
 *store_obj_data.c
*/
int			parser_obj(t_obj **obj, char **tab, int i);

/*
 *particulary_data.c
 */
int			get_size(t_obj *obj, char **tab, int *i);
int			get_axe(t_obj *obj, char **tab, int *i);

/*
 *general_obj_data.c
 */
int			is_light_object(t_obj *obj, char **tab, int *i);
int			csg_operator(t_obj *obj, char **tab, int *i);
int			get_matte_color(t_obj *obj, char **tab, int *i);
int			get_matte_colorv1(t_obj *obj, char **tab, int *i);
int			get_matte_colorv2(t_obj *obj, char **tab, int *i);

/*
 * general_obj_data2.c
 */
int			get_position(t_obj *obj, char **tab, int *i);
int			get_glossy_color(t_obj *obj, char **tab, int *i);
int			get_indice(t_obj *obj, char **tab, int *i);

/*
 * general_obj_data3.c
 */
int			get_matte_factor(t_obj *obj, char **tab, int *i);
int			get_glossy_factor(t_obj *obj, char **tab, int *i);
int			get_specular_factor(t_obj *obj, char **tab, int *i);
int			get_tag(t_obj *obj, char **tab, int *i);
int			get_type(t_obj *obj, char **tab, int *i);

/*
 * general_obj_data4.c
 */
int			get_opacity(t_obj *obj, char **tab, int *i);
int			get_refractive_index(t_obj *obj, char **tab, int *i);
int			get_degrade(t_obj *obj, char **tab, int *i);
int			get_hide_value(t_obj *obj, char **tab, int *i);
int			get_cut_info(t_obj *obj, char **tab, int *i);

/*
 *interpolate.c
 */
double linear_interpolate(double a, double b, double t);
double cosine_interpolate(double a, double b, double t);
double cubic_interpolate(double a, double b, double c, double d, double t);

/*
 *perlin.c
 */
double	smooth_noise_3d(double x, double y, double z);
t_color		perlin_color(t_hit *inter, t_env *e);

/*
 *csg.c
 */

int		binary_object_intersection(t_hit *hit_list, t_hit **inter, t_cam cam);
int		binary_object_union(t_hit *hit_list, t_hit **inter, t_cam cam);
int		binary_object_difference(t_hit *hit_list, t_hit **inter, t_cam cam);
int		binary_object_operation(t_hit *hit_list, t_hit **inter, t_cam cam);

/*
 *color.c
 */
t_color			addcol(t_color a, t_color b);
t_color			scalcol(double a, t_color b);
t_color			mulcol(t_color a, t_color b);
t_color			averagecol(t_color col, int num);
t_color			barycentre_color(t_color c1, t_color c2, t_color c3, double *pondere);


/*
 *textured.c
 */
int			load_all_texture(t_env *e);
t_color			get_texture_color(t_hit *inter,  t_env *e);
t_color			texture_rgb(int u, int v, t_texture *tex);
t_color			texture_color(t_env *e, t_hit *inter, float u, float v);

/*
 *textured_sphere.c
 */
t_color			get_sphere_texture_color(t_hit *inter, t_env *e);

/*
 *textured_plane.c
 */
t_color			get_plane_texture_color(t_hit *inter, t_env *e);
/*
 * procedural_color.c
 */
t_color			get_procedural_texture_color(t_hit *inter);
t_color			get_procedural_texture_color2(t_hit *inter);

/*
 *textured_cuboid.c
 */
t_color			get_cuboid_texture_color(t_hit *inter, t_env *e);
t_color			get_brick_texture_color(t_hit *inter, t_env *e);
t_color			get_chessboard_texture_color(t_hit *inter, t_env *e);

/*
 *textured_cylinder.c
 */
t_color			get_cylinder_texture_color(t_hit *inter, t_env *e);

/*
 *textured_triangle.c
 */
t_color			get_triangle_texture_color(t_hit *inter, t_env *e);

/*
 * textured_cone.c
 */
t_color			get_cone_texture_color(t_hit *inter, t_env *e);

/*
 *base_change.c
 */

t_vector		objectdir_from_cameradir(t_vector dir_in_cam_space, t_base base);
t_vector		objectpoint_from_camerapoint(t_vector point_in_cam_space, t_vector objcenter, t_base objbase);
t_vector		cameradir_from_objdir(t_vector dir_in_obj_space, t_cam cam);
t_vector		camerapoint_from_objpoint(t_vector point_in_obj_space, t_cam cam, t_vector objcenter);

/*
 *list.c
 */
void			add_point_to_intersection_list(t_hit **hit_list, t_hit *news);
int			ft_list_size(t_hit *hit_list);
void			cameralist_from_objlist(t_hit *hit, t_cam cam);
void			copy_hit(t_hit **inter, t_hit *hit_to_copy);
int			pickclosest_intersection(t_hit *hit_list, t_hit **inter, t_cam cam);
void			append_solid_intersection(t_obj *obj, t_ray ray, t_hit **hit_list);
void			append_all_intersection(t_obj *obj, t_ray ray, t_hit **hit_list);
int			findclosest_intersection(t_env  *e, t_ray ray, t_hit **inter);
int			is_point_inside_this_obj(t_obj *obj, t_vector point);
t_obj			*hit_obj(t_obj *obj, t_vector point);
int			is_hit_point_already_inside(t_vector point, t_hit *hit_list);
void			ft_list_merge(t_hit **begin_list1, t_hit **begin_list2);

/*
 * obj_first_position.c
 */
double		radian_from_degree(double angle_degree);
void		rotate_x_obj(t_obj *obj, double angle_degre);
void		rotate_y_obj(t_obj *obj, double angle_degre);
void		rotate_z_obj(t_obj *obj, double angle_degre);

/*
 *translate_camera.c
 */
 void			translate_camera(int key, t_env *e);

/*
 *translate_light.c
 */
 void			translate_light(int key, t_env *e);


/*
 *rotate_camera.c
 */

 void			rotate_camera(int key, t_env *e);
 void			rotate_cam_pos(int key, t_env *e);
 void			rotate_cam_dir(int key, t_env *e);

/*
 * display_cam_info.c
 */
void			display_cam_info(t_env *e);

/*
 * display_obj_info.c
 */
void			display_selected_obj_info1(t_env *e);
void			display_selected_obj_info2(t_env *e);

/*
 * cuboid_utils1.c
 */
void			append_cuboid_inter_pa(t_obj *cuboid , t_ray ray, t_hit **hit);

/*
 * cuboid_utils2.c
 */
void			append_cuboid_inter_ma(t_obj *cuboid , t_ray ray, t_hit **hit);

/*
 * cuboid_utils3.c
 */
void			append_cuboid_inter_pb(t_obj *cuboid , t_ray ray, t_hit **hit);

/*
 * cuboid_utils4.c
 */
void			append_cuboid_inter_mb(t_obj *cuboid , t_ray ray, t_hit **hit);

/*
 * cuboid_utils5.c
 */
void			append_cuboid_inter_pc(t_obj *cuboid , t_ray ray, t_hit **hit);

/*
 * cuboid_utils6.c
 */
void			append_cuboid_inter_mc(t_obj *cuboid , t_ray ray, t_hit **hit);


/*
 *cuboid.c
 */
int			is_point_inside_cuboid(t_obj *cuboid, t_vector point);
void		append_cuboid(t_obj *cuboid, t_ray ray, t_hit **hit);
int			is_point_lying_inside_cuboid(t_obj **cub, t_vector point, t_hit ***hit);

/*
 *cylinder.c
 */
void			append_cylinder(t_obj *cylin, t_ray ray,t_hit **hit_list);
t_vector		calcul_cylin_normal(t_obj **cylin, t_vector point, double t, t_ray ray);
//int			is_point_inside_cylinder(t_obj *obj, t_vector point);

/*
 *sphere.c
 */
//int			is_point_inside_sphere(t_obj *sphere, t_vector point);
void			append_sphere(t_obj *obj, t_ray ray, t_hit **hit_list);
t_vector		calcul_sphere_normal(t_obj **cylin, t_vector point, double t, t_ray ray);


/*
 *cone.c
 */
void			append_cone(t_obj *cone, t_ray ray, t_hit **hit_list);
t_vector		calcul_cone_normal(t_obj **cylin, t_vector point, double t, t_ray ray);


/*
 *plane.c
 */
void			append_plane(t_obj *plane, t_ray ray, t_hit **hit_list);


/*
 *block.c
 */
void			append_block(t_obj *block, t_ray ray, t_hit **hit_list);
t_color			get_block_texture_color(t_hit *inter, t_env *e);

/*
 *brick.c
 */
void			append_brick(t_obj *block, t_ray ray, t_hit **hit_list);

/*
 *box.c
 */
void			append_box(t_obj *block, t_ray ray, t_hit **hit_list);



/*
 *chessboard.c
 */
void			append_chessboard(t_obj *block, t_ray ray, t_hit **hit_list);
void			chessboard_color(t_obj *chessboard, t_hit *inter);

/*
 *triangle.c
 */
void			append_triangle(t_obj *triangle, t_ray ray, t_hit **hit_list);

/*
 * thinring.c
 */
void			append_thinring(t_obj *thingring, t_ray ray, t_hit **hit_list);
t_color			get_thinring_texture_color(t_hit *inter, t_env *e);

/*
 * torus.c
 */
void			append_torus(t_obj *torus, t_ray ray, t_hit **hit_list);
t_color			get_torus_texture_color(t_hit *inter, t_env *e);

/*
 * mobius.c
 */
void			append_mobius(t_obj *torus, t_ray ray, t_hit **hit_list);
t_color			get_mobius_texture_color(t_hit *inter, t_env *e);


/*
 *initializer.c
 */
void			init_camera_axes(t_cam *cam);
t_scene			*initialize_scene(void);
t_light			*initialize_light(t_color color, t_vector pos);
t_env			*init_env(void);

/*
 *line.c
 */
void			line(t_env *e, t_vector p0, t_vector p1);

/*
 *scene.c
 */
void			add_obj_to_scene(t_obj **obj, t_obj *news);
void			add_light_source_to_scene(t_light **light, t_obj *light_point);
void			add_light_obj_to_scene(t_light_obj **light, t_obj *light_obj);

/*
 *draw.c
 */
 void			pixel_put(int x, int y, t_color color, t_env *e);
void			draw_obj(t_env *e);
/*
 *ray.c
 */
void			current_ray(double x, double y, t_env *e, t_ray *ray);

/*
 *light_color.c
 */
void			ft_clamp_val(float *a, float min , float max);
double			ft_maxf(float a, float b);
void			ft_swapf(double *a, double *b);
int			is_not_shadowed(t_env *e, t_ray *shadow, t_hit *inter, double light_dist);
t_color			calculate_matte(t_hit *inter, t_env *e);

/*
 * pthread.c
 */
void		all_thread_render(t_env *e);

/*
 *reflection.c
 */
t_ray			reflect(t_hit *inter,t_ray ray);
/*
 *refraction.c
 */
t_ray			refract(t_hit *inter,t_ray ray, t_env *e);
void			fresnel(t_hit *inter, t_ray ray, t_env *e);

 /*
  *trace.c
  */
t_color			tracer(t_ray ray, int depth, t_env *e);

/*
 *utils.c
 */
void			err_exit(char *str);
int				err_exit2(char *str);
void			ft_clamp_color(t_color *a, double min , double max);
void			ft_clamp_value(double *a, double min, double max);
void			set_inter_info1(t_hit **news, double t, t_vector normal, t_vector point);
void			set_inter_info2(t_hit **news, t_obj **obj, t_ray ray, t_vector ray_origin);
/*
 *destroyer.c
 */
 void			destroy_all(t_env **e);
 void			clear_env(t_env **e);
 void			destroy_intersection_list(t_hit **hit_list);
 void			destroy_scene(t_scene **scene);
 void			destroy_texture_array(t_env *e);

/*
 *obj_hook.c
 */ 
int	obj_hook(t_env *e, int key);

/*
 *camera_hook.c
 */ 
int			cam_hook(int key, t_env *e);
void		menu(void);

/*
 * mouse_hook.c
 */
int			expose_hook_func(t_env *e);
int			close_win(t_env *e);

/*
 * selection.c
 */
int			clicked_obj_info(int x, int y, t_env *e, t_hit **inter);
int			mouse_hook_func(int button, int x, int y, t_env *e);
#endif
