/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 10:27:36 by ibtraore          #+#    #+#             */
/*   Updated: 2017/02/25 06:28:17 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "minilibx_macos/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stddef.h>
# include <time.h>
# include "libft/libft.h"

# define WIDTH 1000
# define HEIGHT 1000
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define SPRITE_NUM 19
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define ESC 53
# define R 15
# define MUSIK_1 83
# define MUSIK_2 84
# define MUSIK_3 85
# define MUSIK_4 86
# define MUSIK_5 87
# define MUSIK_6 88
# define MUSIK_7 89
# define MUSIK_8 91
# define MUSIK_9 92
# define MUSIK_0 82
# define INCREASE_TRANSL_SPEED 12
# define DECREASE_TRANSL_SPEED 13
# define INCREASE_ROT_SPEED 0
# define DECREASE_ROT_SPEED 1

typedef struct		s_textured_img
{
	void			*img;
	char			*imgptr;
	int				endian;
	int				bpp;
	int				width;
	int				height;
	int				size_line;
	int				x;
	int				y;
}					t_textured_img;

typedef struct		s_game
{
	t_textured_img	*texture[12];
	int				textured_map_value;
}					t_game;

typedef struct		s_sprite
{
	double			x_word;
	double			y_word;
	int				texture;
	double			dist_to_cam;
	double			sprite_x_camspace;
	double			sprite_y_camspace;
	int				sprite_x_normalize_0w;
	int				sprite_y_normalize_0w;
	int				height_reduced;
	int				width_reduced;
	int				height_pixel_start;
	int				height_pixel_end;
	int				width_pixel_start;
	int				width_pixel_end;
	int				leftright;
}					t_sprite;

typedef struct		s_env
{
	void			*mlx;
	void			*img;
	void			*win;
	char			*pixel;
	int				size_line;
	int				endian;
	int				bpp;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	int				wallheight;
	int				wallwidth;
	double			posx;
	double			posy;
	double			stepx;
	double			stepy;
	double			camerax;
	int				hit;
	double			perpwalldist;
	int				lineheight;
	int				side;
	int				wallpixelstart;
	int				wallpixelend;
	double			tmp1;
	double			tmp2;
	double			rotspeed;
	double			translspeed;
	int				frame_num;
	double			wallxy;
	double			floorx;
	double			floory;
	double			ponderate_coef;
	double			curr_floorx;
	double			curr_floory;
	double			curr_dist;
	double			floortexx;
	double			floortexy;
	t_game			*g;
	t_sprite		sprite[SPRITE_NUM];
	double			zbuffer[WIDTH];
	int				spriteorder[SPRITE_NUM];
}					t_env;

void				sprite_raycasting(t_env *e);
void				get_sprite_xy_in_camera_space(int i, t_env *e);
void				get_sprite_height_info(int i, t_env *e);
void				sort_sprit_dist(t_env *e);
void				init_sprite(t_env *e);
void				put_pixel(int x, int y, int color, t_env *e);
void				set_color2(t_env *e, t_game *g, int x);
void				init_env(t_env *e);
void				init_env2(t_env *e);
void				init_env3(t_env *e);
int				close_window(t_env *e);
int					untextured_map(int x, int y);
void				draw_wall_ceiling_floor(int x, t_env *e);
int					get_texture_color(t_textured_img *img, int x, int y);
void				untextured_raycasting(t_env *e);
void				textured_raycasting(t_env *e);
int					wait_key_event(int key, t_env *e);
int					wait_key_event2(int key, t_env *e);
int					wait_key_event3(int key, t_env *e);
void				load_textured_sprite_img(t_env *e);
void				load_textured_img(t_env *e);
void				load_untextured_img(t_env *e);
int					textured_map(int x, int y);
void				ray_direction(int x, t_env *e);
void				sidedist_calcul(t_env *e);
void				perpdist_lineheight_calcul(t_env *e);
void				perpdist_lineheight_calcul3(int i, t_env *e);
void				wait_rot_event(int key, t_env *e);
void				wait_translate_event(int keyy, t_env *e);
void				wait_translate_event2(int keyy, t_env *e);
void				wait_translate_event3(int keyy, t_env *e);
void				increase_decrease_movement_speed(int key, t_env *e);
void				load_all_image(t_env *e);
void				load_all_image3(t_env *e);
void				err_exit(char *str, int fd);
void				draw_game(t_env *e, int x);
void				draw_game3(t_env *e, int x);
int					sprite_map(int x, int y);
int					play_music(int key);
void				draw_sprite(t_env *e);
#endif
