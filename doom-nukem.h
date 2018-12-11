/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:01:05 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/11 17:08:46 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <stdlib.h>
# include <math.h>

# define WIN_W 1280
# define WIN_H 720
# define WIN_HS WIN_H / 2 + 250
# define WIN_WS WIN_W / 2 - 120
# define START "PRESS ANY KEY TO START"

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
    double      loop;
    t_player    cam;
    t_move      move;
    t_rot       rot;
    t_bmp       logo;
}               t_e;

int		ft_close(t_e *e);
void    ft_mlx(t_e *e);

int		expose_hook(t_e *e);
int		ft_key_press(int key, t_e *e);
int		ft_key_press2(int key, t_e *e);
int		ft_key_release(int key, t_e *e);
int		ft_mouse_motion(int x, int y, t_e *e);

void	ft_move(t_e *e);

#endif
