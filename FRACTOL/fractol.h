/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:02:19 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/07 22:21:31 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

# define Y 400
# define X 400
# define ESC 53
# define P_ITERATION 83
# define N_ITERATION 86
# define RESET 84
# define CHANGE 85
# define BLOC 85
# define IN 5
# define OUT 4
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define PLUS 69
# define MOIN 78

typedef struct	s_env
{
	int			color;
	int			fract;
	int			bloc;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_img;
	int			bpp;
	int			size_line;
	int			end;
	float		zoom;
	float		xmin;
	float		xmax;
	float		ymin;
	float		ymax;
	float		img_x;
	float		img_y;
	float		rc;
	float		ic;
	float		rz;
	float		iz;
	int			x;
	int			y;
	int			iter_index;
	int			iter_max;
}				t_env;

void			put_pixel(int x, int y, t_env *e);
void			put_pixel_color(int x, int y, t_env *e);
void			init_val(t_env *e);
void			draw_in_window(t_env *e);
void			display_menu(t_env *e);
int				key(int key, t_env *e);
int				mouse_change(int x, int y, t_env *e);
int				mouse_zoom(int key, int x, int y, t_env *e);
void			win(t_env *e);
void			submit_change(t_env *e);
void			fractale_function(t_env *e);
void			fractale_newton(t_env *e, float r, float tmp);
void			fractale_newton_love(t_env *e, float r, float tmp);
void			fractale_neg(t_env *e);
void			fractale_man(t_env *e);
void			fractale_man2(t_env *e, float tmp, float rz, float iz);
void			fractale_man4(t_env *e, float tmp, float rz, float iz);
void			fractale_bship(t_env *e);
void			fractale_jul(t_env *e);
void			fractale_tricorn(t_env *e);
void			fractale_mandelbar4(t_env *e, float tmp,
				float rz, float iz);

#endif
