/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:01:05 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/11 21:01:08 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define WIN_W 1280
# define WIN_H 720
# define HFOV_RAD 30 * 2 * M_PI / 360
# define FOV_RAD 60 * 2 * M_PI / 360
# define WIN_HS WIN_H / 2 + 250
# define WIN_WS WIN_W / 2 - 120
# define START "PRESS ANY KEY TO START"
# define TEXSIZE 64

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_coord_d
{
	double		x;
	double		y;
}				t_coord_d;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_player
{
	t_coord_d	pos;
	t_coord_d	dir;
	t_coord_d	plane;
}				t_player;

typedef struct	s_move
{
	int			forward;
	int			backward;
	int			right;
	int			left;
	int			up;
	int			up2;
	int			fly;
	int			down;
	float		speed;
	float		v;
}				t_move;

typedef struct	s_rot
{
	int			up;
	int			down;
	int			right;
	int			left;
	double		speed;
	double		v;
}				t_rot;

typedef struct		s_floor
{
	t_coord_d	wall;
	double		dist;
	double		weight;
	t_coord_d	tile;
	t_coord		tex;
}				t_floor;

typedef struct	s_bmp
{
	int			width;
	int			height;
	int			size;
	int			*data;
	double		dist;
	double		scale;
	t_coord_d	p;		
}   			t_bmp;

typedef struct	s_wall
{
	int			side;
	double		dist;
	int			height;
	int			size;
	int			top;
	int			bottom;
	double		hit;
    t_coord     tex;
}				t_wall;

typedef struct		s_ray
{
	t_coord_d	dir;
	t_coord		pos;
	t_coord		move;
	t_coord_d	cast;
	t_coord_d	casting;
}				t_ray;

typedef struct  s_e
{
    void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	char		*file;
	int			**map;
	int			bpp;
	int			s_l;
	int			endian;
	int			fd;
    int         startscreen;
    int         start;
    int         end;
    int         texnum;
    int         c;
    double      loop;
    double      alpha;
    double      clr_intensity;
    t_player    cam;
    t_move      move;
    t_rot       rot;
    t_coord     sky;
    t_floor     floor;
    t_wall      wall;
    t_ray       ray;
    t_bmp       logo;
    t_bmp       textures[10];
}               t_e;

int	    	ft_close(t_e *e);
void    	ft_start_screen(t_e *e);
void        ft_mlx(t_e *e);

int 		expose_hook(t_e *e);
int 		ft_key_press(int key, t_e *e);
int 		ft_key_press2(int key, t_e *e);
int 		ft_key_release(int key, t_e *e);
int		    ft_mouse_motion(int x, int y, t_e *e);

void		bmp_loadfile(t_bmp *bmp, char *fname);
t_color		get_pixel_color(t_bmp *img, int x, int y);

void		ft_apply_shadow_to_cf(t_color *c, int y);
void	    ft_apply_shadow_to_spr(t_color *c, int y);
void	    ft_apply_shadow_to_color(t_color *c, double intensity);

void	    ft_move(t_e *e);

#endif
