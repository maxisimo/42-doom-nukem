/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 17:11:44 by thbernar          #+#    #+#             */
/*   Updated: 2019/01/16 17:36:34 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define WIN_W 1280
# define WIN_H 720
# define START "PRESS ANY KEY TO START"
# define SENTENCE1 "THE FUHRER IS DEAD. HOWEVER, A STRANGE MALEDICTION HAS"
# define SENTENCE2 "OCCURED SINCE THEN, RISING THE DEAD FROM THE GRAVE. IT IS"
# define SENTENCE3 "BELIEVED THAT THE CURSE ORIGINATED FROM THE WOLFENSTEIN"
# define SENTENCE4 "CASTLE WHERE THE NAZIS HID A PIECE OF INESTIMABLE VALUE :"
# define SENTENCE5 "THE SKULL OF DOOM. KILL THE UNDEAD AND RETRIEVE THAT SKULL"
# define SENTENCE6 "TO HOPEFULLY END THE CURSE. YOU KNOW THAT CASTLE BETTER"
# define SENTENCE7 "THAN ANYONE ELSE WHICH IS WHY YOU ARE OUR BEST HOPE."
# define SENTENCE8 "GODSPEED, AGENT BLAZKOWICZ."
# define OPEN "Press 'E' to open"
# define CLOSE "Press 'E' to close"
# define END "Press 'E' to end the curse"
# define HFOV_RAD 30 * 2 * M_PI / 360
# define FOV_RAD 60 * 2 * M_PI / 360
# define WIN_HS WIN_H / 2 + 250
# define WIN_WS WIN_W / 2 - 120
# define WIN_HD WIN_H / 2
# define WIN_WD WIN_W / 2 - 90
# define WINDOW 7
# define HDOOR 8
# define VDOOR 9
# define HDOOR_O -8
# define VDOOR_O -9
# define DOOR1 7
# define DOOR2 8
# define POSTER 9

typedef struct		s_coord
{
	int				x;
	int				xx;
	int				y;
}					t_coord;

typedef struct		s_coord_d
{
	double			x;
	double			y;
}					t_coord_d;

typedef struct		s_player
{
	t_coord_d		pos;
	t_coord_d		dir;
	t_coord_d		plane;
}					t_player;

typedef struct		s_ray
{
	t_coord_d		dir;
	t_coord_d		pos;
	t_coord			step;
}					t_ray;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_bmp
{
	int				width;
	int				height;
	int				size;
	int				*data;
	double			dist;
	double			scale;
	t_coord_d		p;
}					t_bmp;

typedef struct		s_weapon
{
	t_bmp			img;
	t_bmp			img2;
	t_bmp			scope;
	int				is_fired;
	int				fire_count;
}					t_weapon;

typedef struct		s_circle
{
	int				x;
	int				y;
	int				xc;
	int				yc;
	int				d;
	int				i;
}					t_circle;

typedef struct		s_spr
{
	int				screenx;
	int				height;
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
	int				width;
	int				stripe;
	int				texx;
	int				texy;
	int				y;
	int				x;
	int				clr;
	double			spr_x;
	double			spr_y;
	double			invdet;
	double			change_x;
	double			change_y;
	double			dist;
	t_coord_d		pos;
	t_bmp			*img;
}					t_spr;

typedef struct		s_enemy
{
	t_spr			sprite;
	t_coord_d		pos;
	int				step;
	int				life;
	int				type;
	int				dying;
}					t_enemy;

typedef struct		s_dir
{
	int				up;
	int				down;
	int				right;
	int				left;
	double			s;
	float			v;
}					t_dir;

typedef struct		s_floor
{
	double			x;
	double			y;
	double			curdist;
	double			weight;
	t_coord			tex;
	t_coord_d		curfloor;
}					t_floor;

typedef struct		s_wall
{
	double			dist;
	double			clr_intensity;
	t_coord_d		side_dist;
	t_coord_d		deltadist;
}					t_wall;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*fname;
	char			*img_data;
	int				**map;
	int				n[3];
	int				spr_num;
	int				p_count;
	int				start;
	int				end;
	int				lineheight;
	int				side;
	int				speed;
	int				c;
	int				texx;
	int				texy;
	int				startscreen;
	int				screen_win;
	int				texnum;
	int				current_thread;
	int				is_weapon;
	int				mapx;
	int				mapy;
	int				enemies_count;
	int				enemies_count2;
	int				jump;
	int				jumping;
	int				fly;
	int				crouch;
	int				size;
	int				poster;
	int				ammo;
	int				click;
	struct s_app	*main_a;
	double			wallx;
	double			distplayer;
	double			loop;
	double			camx;
	double			zbuffer[WIN_W];
	double			life;
	double			life2;
	t_bmp			startscreentxt;
	t_bmp			logo;
	t_bmp			game_over;
	t_bmp			game_win;
	t_bmp			textures[11];
	t_bmp			sprites[16];
	t_coord			map_size;
	t_coord			p;
	t_coord_d		pos;
	t_dir			move;
	t_dir			rot;
	t_ray			ray;
	t_player		cam;
	t_coord			sky;
	t_floor			floor;
	t_weapon		weapon;
	t_enemy			*enemies;
	t_wall			wall;
}					t_app;

void				ft_app_allocmap(t_app *app);
void				ft_app_writemap(t_app *app);
void				ft_app_init(t_app *app);

int					expose_hook(t_app *a);
int					ft_key_press(int key, t_app *app);
int					ft_key_press2(int key, t_app *app);
int					ft_key_release(int key, t_app *app);
int					ft_button_press(int button, int x, int y, t_app *app);
int					ft_button_release(int button, int x, int y, t_app *app);
int					ft_mouse_motion(int x, int y, t_app *app);

void				ft_move(t_app *a);
void				ft_rotate(t_app *a);

void				ft_doors(t_app *a);
void				draw_wall(int x, int start, int end, t_app *a);
void				ft_door_side(t_app *a);

void				ft_pthread(t_app *a);
void				*raycasting(void *tab);

void				draw_wall(int x, int start, int end, t_app *a);
int					ft_draw(t_app *a);

void				ft_apply_shadow_to_cf(t_color *c, int y);
void				ft_apply_shadow_to_spr(t_color *c, int y);
void				ft_apply_shadow_to_color(t_color *c, double intensity);

void				draw_minimap(t_app *a);
void				put_pxl_to_img(t_app *a, int x, int y, int color);
void				draw_player(t_app *a);

int					ft_rgb_to_hex(t_color c);
void				ft_put_pxl_to_img(t_app *a, t_color c, int x, int y);
void				ft_put_circle_to_img(t_app *a, t_circle *c);
void				ft_put_bmp_to_img(t_app *a, t_bmp bmp, int x, int y);
void				ft_choose_color(int x, int start, t_app *a);

int					ft_close(t_app *app);
void				ft_error(char *s);
void				ft_free_strsplit(char **array);
void				ft_init_tex_fc(t_app *a);
void				ft_info(t_app *a);

void				bmp_loadfile(t_bmp *bmp, char *fname, int w, int h);
t_color				get_pixel_color(t_bmp *img, int x, int y);

void				weapons_draw_weapon(t_app *a);

void				sort_sprites(t_app *a);
void				sprites_draw(t_app *a, t_enemy *e);
void				sprites_get_pos(t_app *a);

void				textures_load(t_app *a);
void				sprites_load(t_app *a);

void				startscreen_draw(t_app *a);
void				story(t_app *a);
void				game_over(t_app *a);

void				enemies_init(t_app *a);
void				enemies_dying(t_app *a, t_enemy *e, t_spr *s);
void				enemies_draw(t_app *a);

void				ft_poster(t_app *a);

#endif
