/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 00:22:52 by ibtraore          #+#    #+#             */
/*   Updated: 2017/01/26 00:32:29 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include <math.h>
# include "minilibx_macos/mlx.h"
//# include <mlx.h>

# define WIDTH 2560
# define HEIGHT 1440
# define BPP 32
# define ZOOM_UP 2 //69
# define ZOOM_DOWN 8//78
# define DOWN 126
# define UP 125
# define LEFT 123
# define RIGHT 124
# define ROT_X_P 12 //84
# define ROT_X_N 13 //83
# define ROT_Y_P 1 //87
# define ROT_Y_N 0 //86
# define ROT_Z_P 6 //91
# define ROT_Z_N 7 //89
# define RESET 14 //85
# define ESC 53

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
	double			w;
	int				color;
}					t_point;

typedef struct		s_line
{
	t_point			**points;
}					t_line;

typedef struct		s_map
{
	t_line			**lines;
}					t_map;

typedef struct		s_matrix
{
	double			a[4][4];
}					t_matrix;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_point			*point;
	int				line;
	int				col;
	t_map			*map;
	int				endian;
	int				size_line;
	void			*img;
	char			*pixel;
	int				bpp;
	double			zoom;
	t_matrix		*m;
	double			xcenter;
	double			ycenter;
	double			xstart;
	double			ystart;
	double			dx;
	double			flagdx;
	double			dy;
	double			flagdy;
	double			flag;
}					t_env;

int					key_hook(int key, t_env *e);
void				new_point(t_point *p, t_matrix *m, t_env *e);
t_matrix			*init_matrix(void);
void				init_env(t_env *e);
void				set_image(t_env *e);
void				initialize_env(t_env *e);
void				ft_err_exit(char *str);
void				ft_destroy_tab(char **tab);
void				ft_destroy_map(t_env *e);
void				set_isometric_function(t_env *e);
void				line (t_env *e, t_point p0, t_point p1);
int					ft_color_palette(t_point p0, t_point p1);
void				get_map(t_map **map, t_env *e);
void				ft_reader(t_env *e, char *file);
t_matrix			*ft_rotate_x(double x);
t_matrix			*ft_rotate_y(double x);
t_matrix			*ft_rotate_z(double x);
t_matrix			*ft_translate(int tx, int ty, int tz);
t_matrix			*ft_scale(double sx, double sy, double sz);
void				all_points(t_env *e, t_matrix *m);
void				wait_translate_left_right_event(int key, t_env *e);
void				wait_translate_up_down_event(int key, t_env *e);
void				wait_zoom_event(int key, t_env *e);
void				wait_rotate_x_event(int key, t_env *e);
void				wait_rotate_y_event(int key, t_env *e);
void				wait_rotate_z_event(int key, t_env *e);
void				wait_others_event(int key, t_env *e);

#endif
