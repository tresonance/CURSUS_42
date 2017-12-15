/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmjaku <kmjaku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 02:27:37 by thchin            #+#    #+#             */
/*   Updated: 2017/12/15 15:32:33 by kmjaku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <OpenCL/opencl.h>
# include <SDL.h>
# include <SDL_image.h>
# include "../libft/libft.h"
# include <gtk/gtk.h>

# define KEY event.key.keysym.sym
# define BUTTON event.button.button

# define MAXSOURCESIZE (0x100000)
# define WIDTH 800
# define HEIGHT 600

# define SPHERE 0
# define PLANE 1
# define CONE 2
# define CYLINDER 3
# define BOX 4
# define SKY 5
# define TRIANGLE 6
# define PARABOLOID 7
# define TORE 8

# define PARRALEL 0
# define POINT 1

# define DIFFUSE 0
# define REFLECTIVE 1
# define REFRACTIVE 2
# define TRANSPARANT 3

typedef struct			s_gtk
{
	GtkWidget			*window;
	GtkWidget			*label;
	GtkWidget			*button_open;
	GtkWidget			*button_quit;
	GtkWidget			*layout;
	GtkWidget			*image;
	GtkWidget			*menu_bar;
}						t_gtk;

typedef struct			s_image
{
	int					width;
	int					height;
}						t_image;

typedef struct			s_aabb
{
	cl_float4			min;
	cl_float4			max;
}						t_aabb;

typedef struct			s_bvh
{
	cl_float4			min;
	cl_float4			max;
	unsigned int		count;
	int					obj_id;
	unsigned int		codes;
	unsigned int		parent;
	unsigned int		childa;
	unsigned int		childb;
}						t_bvh;

typedef struct			s_prim
{
	int					type;
	cl_float4			pos;
	cl_float4			pos1;
	cl_float4			pos2;
	cl_float4			color;
	cl_float4			rot;
	float				size;
	int					mat;
	int					text;
	int					bump;
}						t_prim;

typedef struct			s_material
{
	int					type;
	float				roughness;
	float				coef;
}						t_material;

typedef struct			s_text
{
	int					id;
	int					pos;
	float				xoffset;
	float				yoffset;
	cl_float4			startoffset;
}						t_text;

typedef struct			s_light
{
	cl_float4			pos;
	cl_float4			dir;
	cl_float4			color;
	float				intensity;
	int					type;
}						t_light;

typedef struct			s_cam
{
	cl_float4			pos;
	cl_float4			dir;
	cl_float4			lookat;
	cl_float4			normal;
	cl_float4			right;
	cl_float4			up;
}						t_cam;

typedef struct			s_info
{
	int					nb_prim;
	int					nb_light;
	int					nb_text;
	int					nb_mat;
	int					nb_bump;
	int					aa;
}						t_info;

typedef struct			s_noise
{
	float				tmpx;
	float				tmpy;
	int					x0;
	int					y0;
	int					gi0;
	int					gi1;
	int					gi2;
	int					gi3;
	float				tmp;
	float				s;
	float				t;
	float				u;
	float				v;
	float				cx;
	float				cy;
	float				li1;
	float				li2;
}						t_noise;

typedef struct			s_marble
{
	float				xperiod;
	float				yperiod;
	float				turbpower;
	float				turbsize;
}						t_marble;

typedef struct			s_bump
{
	float				tl;
	float				l;
	float				bl;
	float				b;
	float				br;
	float				r;
	float				tr;
	float				t;
}						t_bump;

typedef struct			s_opencl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_program			program;
	cl_command_queue	command_queue;
	cl_kernel			renderkernel;
	cl_mem				buffer;
	cl_mem				cam;
	cl_mem				prim;
	cl_mem				material;
	cl_mem				text;
	cl_mem				bump;
	cl_mem				light;
	cl_mem				info;
	cl_mem				image;
	cl_mem				data;
	cl_mem				sky;
	cl_mem				sky_data;
	cl_mem				bump_image;
	cl_mem				bump_data;
}						t_opencl;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Event			event;
	SDL_Surface			*ptr;
}						t_sdl;

typedef struct			s_scene
{
	t_gtk				gtk;
	t_opencl			cl;
	t_sdl				sdl;
	t_cam				*cam;
	t_prim				*prim;
	t_light				*light;
	cl_float4			*image;
	t_image				*data;
	Uint8				*sky;
	t_image				*sky_data;
	t_info				*info;
	SDL_Surface			*sky_surface;
	cl_float4			*bump_image;
	t_image				*bump_data;
	t_material			*mat;
	t_text				*text;
	t_text				*bump;
	unsigned int		permtable[512];
	double				old_time;
	double				time;
	double				frametime;
	double				accumtime;
	double				total_time;
	double				total_time_1;
	double				total_time_2;
	int					i;
	int					j;
	int					k;
	int					p_entiere;
	float				p_decimale;
}						t_scene;

typedef struct			s_poly
{
	float				a;
	float				b;
	float				c;
	float				d;
	float				e;
	float				p;
	float				q;
	float				r;
	float				u;
	float				v;
	float				t;
	float				s;
	float				delta;
}						t_poly;

void					print_float4(cl_float4 v);

cl_float4				conjugate(cl_float4 v1);
cl_float4				hamilton_product(cl_float4 v1, cl_float4 v2);
cl_float4				addvect(cl_float4 v1, cl_float4 v2);
cl_float4				subvect(cl_float4 v1, cl_float4 v2);
cl_float4				normalize(cl_float4 v);
cl_float4				crossvect(cl_float4 v1, cl_float4 v2);
cl_float4				scalevect(cl_float4 v1, float s);
float					dotproduct(cl_float4 v1, cl_float4 v2);

void					clear_scene(t_scene *scene);
void					move_object(t_scene *scene);
int						init_skydome(SDL_Surface *img, t_scene *scene);
int						init_sky(SDL_Surface *img, t_scene *scene);
int						init_scene(char *filename, t_scene *scene);
void					copy_scene(t_scene *scene, t_opencl *cl);

void					key_event(t_scene *scene, t_sdl sdl, SDL_Event event);

void					update_time(t_scene *scene);

cl_program				build_source(cl_context context, cl_device_id device_id,
						char *name);
cl_kernel				build_renderkernel(cl_program program,
						cl_context context, t_scene *scene, t_opencl *cl);

void					init_permtable(t_scene *scene);
float					turbulence(unsigned int perm[512], float x, float y,
						float res);
cl_float4				*create_perlin(unsigned int perm[512], t_image *data,
						int size);
cl_float4				*create_marble(unsigned int perm[512], t_image *data,
						t_marble m);
cl_float4				*conv_normalmap(t_image *data, cl_float4 *pmap);

void					selected_obj_event(SDL_Event event, t_scene *scene);
void					translate_obj(SDL_Event event, t_scene *scene);

void					show_perlinmap(cl_float4 *image, t_image *info,
						t_sdl sdl);
void					show_normalmap(cl_float4 *image, t_image *info,
						t_sdl sdl);
void					flip(t_sdl sdl, SDL_Surface *ptr);

void					count_obj(char *str, t_scene *scene);
int						convert_define(char *str);
int						convert_define2(char *str);
void					init_prim(t_scene *scene);

void					parse_bump(char *str, t_scene *scene);
void					parse_text(char *str, t_scene *scene);
void					parse_cam(char *str, t_scene *scene);
void					parse_prim(char *str, t_scene *scene);
void					parse_mat(char *str, t_scene *scene);
void					parse_light(char *str, t_scene *scene);

void					parse_cam_co(char *str, char **str2, t_cam **cam);
void					parse_prim_co(char *str, char **str2, t_scene *scene,
						int *i);
void					parse_text_co(char *str, char **str2, t_scene *scene,
						int *i);
void					parse_bump_co(char *str, char **str2, t_text *bump,
						int *i);
void					parse_mat_co(char *str, char **str2, t_scene *scene,
						int *i);
void					parse_light_co(char *str, char **str2, t_light *light,
						int *i);
void					init_zero(t_scene *scene);

void					gtk_window_create(t_scene *e, gint width, gint height,
						gchar *title);
GtkWidget				*gtk_label(gchar *label_content);
GtkWidget				*gtk_button(gchar *button_name);
int						gtk_launch(int ac, char *av[]);
void					destroy(GtkWidget *widget, gpointer data);
void					gtk_menu(t_gtk *e);
void					gtk_dialog(t_scene *scene, gpointer data);
void					destroy_exit(GtkWidget *widget, gpointer data);
gchar					*name_of_members(void);
void					gtk_layout(t_gtk *e);
GtkWidget				*get_live_info(t_scene *e, char *info);
GtkWidget				*get_live_time_info_1(t_scene *e, char *info);
GtkWidget				*get_live_time_info_2(t_scene *e, char *info);
char					*convert(t_scene *e, double nb);
void					window_sdl(t_scene *e, int i);

int						rt_launch(char *filename);

void					clean_double_tab(char **tab, char **tab1);
void					init_opencl(t_scene *scene, t_opencl *cl);
void					print_time(t_scene *e, cl_event event, int i);
void					render(t_scene *e, t_sdl sdl, t_opencl cl);
void					clear_scene1(t_scene *scene);
void					clear_scene(t_scene *scene);

#endif
