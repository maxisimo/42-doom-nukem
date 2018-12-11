/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:41:32 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/11 20:59:06 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void		ft_draw_sky(int x, int start, t_e *e)
{
	int		i;
	int		clr;
	t_color	c1;

	i = 0;
	e->alpha = acos(e->cam.dir.x);
	if (e->alpha != e->alpha)
		e->alpha = M_PI;
	if (e->cam.dir.y < 0)
		e->alpha *= -1;
	e->alpha += M_PI;
	e->alpha += x * FOV_RAD / WIN_W - HFOV_RAD;
	e->alpha += (e->alpha < 0) ? 2 * M_PI : 0;
	e->alpha -= (e->alpha > 2 * M_PI) ? 2 * M_PI : 0;
	e->sky.x = e->alpha * e->textures[8].width / (2 * M_PI);
	while (i <= start)
	{
		e->sky.y = e->textures[8].height - i * e->textures[8].height / (WIN_H);
		c1 = get_pixel_color(&e->textures[8], (int)e->sky.x, (int)e->sky.y);
		clr = ft_rgb_to_hex(c1);
		ft_memcpy(e->data + 4 * WIN_W * i + x * 4,
				&clr, sizeof(int));
		i++;
	}
}

static void		ft_floor(int x, int y, t_e *e)
{
	t_color	c1;

	y = e->end;
	ft_init_tex_fc(e);
	while (y < WIN_H)
	{
		e->floor.dist = WIN_H / (2 * y - WIN_H - 2 * e->rot.v);
		e->floor.weight = e->floor.dist * (2 * e->wall.size + 1) /
			e->wall.dist * (e->move.v / (2 * e->wall.size + 1) - 1);
		e->floor.tile.x = e->floor.weight * e->floor.wall.x +
			(1 - e->floor.weight) * e->cam.pos.x;
		e->floor.tile.y = e->floor.weight * e->floor.wall.y +
			(1 - e->floor.weight) * e->cam.pos.y;
		e->floor.tex.x = (int)(e->floor.tile.x * TEXSIZE) % TEXSIZE;
		e->floor.tex.y = (int)(e->floor.tile.y * TEXSIZE) % TEXSIZE;
		c1 = get_pixel_color(&e->textures[6], e->floor.tile.x, e->floor.tile.y);
		ft_apply_shadow_to_cf(&c1, y);
		ft_put_pxl_to_img(e, c1, x, y);
		y++;
	}
}

static void		ft_ceilling(int x, int y, t_e *e)
{
	t_color	c1;

	y = e->end;
	ft_init_tex_fc(e);
	while (y < WIN_H)
	{
		e->floor.dist = WIN_H / (2 * y - WIN_H - 2 * e->rot.v);
		e->floor.weight = e->floor.dist * (2 * e->wall.size + 1) /
			e->wall.dist * (e->move.v / (2 * e->wall.size + 1) - 1);
		e->floor.tile.x = e->floor.weight * e->floor.wall.x +
			(1 - e->floor.weight) * e->cam.pos.x;
		e->floor.tile.y = e->floor.weight * e->floor.wall.y +
			(1 - e->floor.weight) * e->cam.pos.y;
		e->floor.tex.x = (int)(e->floor.tile.x * TEXSIZE) % TEXSIZE;
		e->floor.tex.y = (int)(e->floor.tile.y * TEXSIZE) % TEXSIZE;
		c1 = get_pixel_color(&e->textures[3], e->floor.tile.x, e->floor.tile.y);
		ft_apply_shadow_to_cf(&c1, y);
		ft_put_pxl_to_img(e, c1, x, (WIN_H - y));
		y++;
	}
}

void			ft_choose_color(int x, int start, t_e *e)
{
	t_color c1;

	e->texnum = e->map[e->ray.pos.y][e->ray.pos.x] - 1;
	c1 = get_pixel_color(&e->textures[e->texnum], e->wall.tex.x, e->wall.tex.y);
	ft_apply_shadow_to_color(&c1, e->clr_intensity);
	ft_put_pxl_to_img(e, c1, x, start);
}

void			draw_wall(int x, int start, int end, t_e *e)
{
	int		y;

	y = start;
	if (e->wall.side == 0)
		e->wall.hit = e->cam.pos.y + e->wall.dist * e->ray.dir.y;
	else
		e->wall.hit = e->cam.pos.x + e->wall.dist * e->ray.dir.x;
	e->wall.hit -= floor(e->wall.hit);
	e->wall.tex.x = (int)(e->wall.hit * TEXSIZE);
	if (e->c == 0)
    {
		ft_floor(x, start, e);
        ft_ceiling(x, start, e);
    }
	else if (e->c == 1)
		ft_draw_sky(x, start, e);
	while (++start <= end - 1)
	{
		e->wall.tex.y = (start - WIN_H / 2 + (e->wall.height / 2)
			* (-e->move.v + 1)) - e->rot.v;
		e->wall.tex.y = abs(e->wall.tex.y);
		ft_choose_color(x, start, e);
	}
}

int				ft_draw(t_e *e)
{
	int		n[3];

	e->img = mlx_new_image(e->win, WIN_W, WIN_H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->s_l, &e->endian);
	if (e->startscreen == 0)
	{
		ft_pthread(e);
		sprites_draw(e);
		draw_minimap(e);
		draw_player(e);
		weapons_draw_weapon(e);
		ft_move(e);
	}
	else
		startscreen_draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
	mlx_do_sync(e->mlx);
	return (0);
}