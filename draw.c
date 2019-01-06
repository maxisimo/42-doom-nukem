/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:07:10 by lchappon          #+#    #+#             */
/*   Updated: 2019/01/06 18:42:31 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		ft_doors_info(t_app *a)
{
	if (((a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == HDOOR &&
			fabs(a->cam.dir.x) > fabs(a->cam.dir.y)) ||
			(a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == VDOOR &&
			fabs(a->cam.dir.x) < fabs(a->cam.dir.y))) &&
			a->move.v <= 1)
		mlx_string_put(a->mlx, a->win, WIN_W / 2 - 90, WIN_H / 2, 0xFFFFFF,
				"Press 'E' to open");
	if (((a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == HDOOR_O &&
			fabs(a->cam.dir.x) > fabs(a->cam.dir.y) &&
			a->map[(int)a->pos.x][(int)a->pos.y] != HDOOR_O) ||
			(a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == VDOOR_O &&
			fabs(a->cam.dir.x) < fabs(a->cam.dir.y) &&
			a->map[(int)a->pos.x][(int)a->pos.y] != VDOOR_O)) &&
			a->move.v <= 1)
		mlx_string_put(a->mlx, a->win, WIN_W / 2 - 90, WIN_H / 2, 0xFFFFFF,
				"Press 'E' to close");
	if ((a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == 13 ||
			a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == 13) &&
			a->move.v <= 1)
		mlx_string_put(a->mlx, a->win, WIN_W / 2 - 90, WIN_H / 2, 0xFFFFFF,
				"Press 'E' to end");
}

static void		ft_draw_sky(int x, int start, t_app *a)
{
	double	alpha;
	int		i;
	int		clr;
	t_color	c1;

	i = 0;
	alpha = asin(a->cam.dir.x);
	if (alpha != alpha)
		alpha = M_PI;
	if (a->cam.dir.y < 0)
		alpha *= -1;
	alpha += M_PI;
	alpha += x * FOV_RAD / WIN_W - HFOV_RAD;
	alpha += (alpha < 0) ? 2 * M_PI : 0;
	alpha -= (alpha > 2 * M_PI) ? 2 * M_PI : 0;
	a->sky.x = alpha * a->textures[9].width / (2 * M_PI);
	while (i <= start)
	{
		a->sky.y = (WIN_H / 2 + i - a->rot.v) * a->textures[9].height / WIN_H;
		c1 = get_pixel_color(&a->textures[9], a->sky.x, a->sky.y);
		clr = ft_rgb_to_hex(c1);
		ft_memcpy(a->img_data + 4 * WIN_W * i + x * 4,
				&clr, sizeof(int));
		i++;
	}
}

static void		ft_ceiling(int x, int y, t_app *a)
{
	t_color	c1;

	y = 0;
	ft_init_tex_fc(a);
	while (y < a->start)
	{
		a->floor.curdist = WIN_H / (2.0 * y - WIN_H - 2 * a->rot.v);
		a->floor.weight = a->floor.curdist * (2 * a->size + 1) /
			a->wall.dist * (a->move.v / (2 * a->size + 1) - 1);
		a->floor.curfloor.x = a->floor.weight * a->floor.x +
			(1.0 - a->floor.weight) * a->pos.y;
		a->floor.curfloor.y = a->floor.weight * a->floor.y +
			(1.0 - a->floor.weight) * a->pos.x;
		a->floor.tex.x = (int)(a->floor.curfloor.x * TEXSIZE) % TEXSIZE;
		a->floor.tex.y = (int)(a->floor.curfloor.y * TEXSIZE) % TEXSIZE;
		c1 = get_pixel_color(&a->textures[2], a->floor.tex.x, a->floor.tex.y);
		if (a->c == 0)
			ft_apply_shadow_to_cf(&c1, y - WIN_H - a->rot.v);
		ft_put_pxl_to_img(a, c1, x, y);
		y++;
	}
}

static void		ft_floor(int x, int y, t_app *a)
{
	t_color	c1;

	y = a->end;
	ft_init_tex_fc(a);
	while (y < WIN_H)
	{
		a->floor.curdist = WIN_H / (2.0 * y - WIN_H - 2 * a->rot.v);
		a->floor.weight = a->floor.curdist / a->wall.dist * (a->move.v + 1);
		a->floor.curfloor.x = a->floor.weight * a->floor.x +
			(1.0 - a->floor.weight) * a->pos.y;
		a->floor.curfloor.y = a->floor.weight * a->floor.y +
			(1.0 - a->floor.weight) * a->pos.x;
		a->floor.tex.x = (int)(a->floor.curfloor.x * TEXSIZE) % TEXSIZE;
		a->floor.tex.y = (int)(a->floor.curfloor.y * TEXSIZE) % TEXSIZE;
		a->floor.tex.y = abs(a->floor.tex.y);
		c1 = get_pixel_color(&a->textures[5], a->floor.tex.x, a->floor.tex.y);
		if (a->c == 0)
			ft_apply_shadow_to_cf(&c1, y - a->rot.v - a->move.v * TEXSIZE);
		ft_put_pxl_to_img(a, c1, x, y);
		y++;
	}
}

void			ft_door_side_entry(t_app *a)
{
	if (a->map[a->mapy][a->mapx] < WINDOW &&
			a->side == 0 && a->ray.dir.x < 0 &&
			a->map[a->mapy][a->mapx + 1] == VDOOR_O)
		a->texnum = DOOR2;
	else if (a->map[a->mapy][a->mapx] < WINDOW &&
			a->side == 0 && a->ray.dir.x > 0 &&
			a->map[a->mapy][a->mapx - 1] == VDOOR_O &&
			(a->map[a->mapy][a->mapx - 2] <= 0 ||
			a->map[a->mapy][a->mapx - 2] >= WINDOW))
		a->texnum = DOOR2;
	if (a->map[a->mapy][a->mapx] < WINDOW &&
			a->side == 1 && a->ray.dir.y < 0 &&
			a->map[a->mapy + 1][a->mapx] == HDOOR_O)
		a->texnum = DOOR2;
	else if (a->map[a->mapy][a->mapx] < WINDOW &&
			a->side == 1 && a->ray.dir.y > 0 &&
			a->map[a->mapy - 1][a->mapx] == HDOOR_O &&
			(a->map[a->mapy - 2][a->mapx] <= 0 ||
			a->map[a->mapy - 2][a->mapx] >= WINDOW))
		a->texnum = DOOR2;
}

void			ft_door_side(t_app *a)
{
	if (a->map[a->mapy][a->mapx] == VDOOR && a->side == 0)
		a->texnum = DOOR2;
	if (a->map[a->mapy][a->mapx] == HDOOR && a->side == 1)
		a->texnum = DOOR2;
	ft_door_side_entry(a);
}

void			ft_choose_color(int x, int start, t_app *a)
{
	t_color c1;

	a->texnum = a->map[a->mapy][a->mapx] - 1;
	if (a->texnum >= DOOR2)
		a->texnum = DOOR1;
	if (a->texy < 0 && a->texnum == DOOR1)
		a->texnum = DOOR2;
	ft_door_side(a);
	if (a->texy < 0)
		a->texy += TEXSIZE;
	c1 = get_pixel_color(&a->textures[a->texnum], a->texx, a->texy);
	if (a->c == 0)
		ft_apply_shadow_to_color(&c1, a->wall.clr_intensity);
	ft_put_pxl_to_img(a, c1, x, start);
}

void			draw_wall(int x, int start, int end, t_app *a)
{
	if (a->side == 0)
		a->wallx = a->pos.x + a->wall.dist * a->ray.dir.y;
	else
		a->wallx = a->pos.y + a->wall.dist * a->ray.dir.x;
	a->wallx -= floor(a->wallx);
	a->texx = (int)(a->wallx * TEXSIZE);
	a->texx = TEXSIZE - a->texx - 1;
	if (a->c == 0)
		ft_ceiling(x, start, a);
	else if (a->c == 1)
		ft_draw_sky(x, start, a);
	ft_floor(x, start, a);
	while (start <= end - 1)
	{
		a->texy = (start - WIN_H / 2 + (a->lineheight / 2)
				* (-a->move.v + 1) - a->rot.v) * TEXSIZE / a->lineheight;
		a->texy %= TEXSIZE;
		ft_choose_color(x, start, a);
		start++;
	}
}

int				ft_draw(t_app *a)
{
	int		n[3];

	a->img = mlx_new_image(a->win, WIN_W, WIN_H);
	a->img_data = mlx_get_data_addr(a->img, &n[0], &n[1], &n[2]);
	if (a->startscreen == 0)
	{
		if (a->life > 0)
		{
			ft_pthread(a);
			a->life2 = a->life;
			enemies_draw(a);
			draw_minimap(a);
			draw_player(a);
			weapons_draw_weapon(a);
			ft_move(a);
			ft_rotate(a);
			mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
			ft_doors_info(a);
			mlx_string_put(a->mlx, a->win, 10, WIN_H - 30, 0xFFFFFF, ft_strjoin(ft_itoa(a->life), " HEALTH POINTS"));
			mlx_string_put(a->mlx, a->win, 10, WIN_H - 50, 0xFFFFFF, ft_strjoin(ft_itoa(a->ammo), " AMMUNITIONS"));
			mlx_string_put(a->mlx, a->win, 10, WIN_H - 70, 0xFFFFFF, ft_strjoin(ft_itoa(a->enemies_count2), " ENEMIES"));
		}
		else
			mlx_string_put(a->mlx, a->win, WIN_WS, WIN_HS, 0xFFFFFF, "GAME OVER");
	}
	else
		startscreen_draw(a);
	mlx_destroy_image(a->mlx, a->img);
	mlx_do_sync(a->mlx);
	return (0);
}
