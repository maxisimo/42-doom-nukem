/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:07:10 by lchappon          #+#    #+#             */
/*   Updated: 2019/01/16 17:12:18 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
	a->sky.x = alpha * a->textures[10].width / (2 * M_PI);
	while (i <= start)
	{
		a->sky.y = (WIN_H / 2 + i - a->rot.v) * a->textures[10].height / WIN_H;
		c1 = get_pixel_color(&a->textures[10], a->sky.x, a->sky.y);
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
		a->floor.tex.x = (int)(a->floor.curfloor.x *
			a->textures[a->texnum].width) % a->textures[a->texnum].width;
		a->floor.tex.y = (int)(a->floor.curfloor.y *
			a->textures[a->texnum].height) % a->textures[a->texnum].height;
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
		a->floor.tex.x = (int)(a->floor.curfloor.x *
			a->textures[a->texnum].width) % a->textures[a->texnum].width;
		a->floor.tex.y = (int)(a->floor.curfloor.y *
			a->textures[a->texnum].height) % a->textures[a->texnum].height;
		a->floor.tex.y = abs(a->floor.tex.y);
		c1 = get_pixel_color(&a->textures[5], a->floor.tex.x, a->floor.tex.y);
		if (a->c == 0)
			ft_apply_shadow_to_cf(&c1, y - a->rot.v - a->move.v *
				a->textures[a->texnum].width);
		ft_put_pxl_to_img(a, c1, x, y);
		y++;
	}
}

void			draw_wall(int x, int start, int end, t_app *a)
{
	a->texnum = a->map[a->mapy][a->mapx] - 1;
	if (a->side == 0)
		a->wallx = a->pos.x + a->wall.dist * a->ray.dir.y;
	else
		a->wallx = a->pos.y + a->wall.dist * a->ray.dir.x;
	a->wallx -= floor(a->wallx);
	a->texx = (int)(a->wallx * a->textures[a->texnum].width);
	a->texx = a->textures[a->texnum].width - a->texx - 1;
	if (a->c == 0)
		ft_ceiling(x, start, a);
	else if (a->c == 1)
		ft_draw_sky(x, start, a);
	ft_floor(x, start, a);
	while (start <= end - 1)
	{
		a->texy = (start - WIN_H / 2 + (a->lineheight / 2)
					* (-a->move.v + 1) - a->rot.v) *
						a->textures[a->texnum].height / a->lineheight;
		a->texy %= a->textures[a->texnum].height;
		ft_choose_color(x, start, a);
		start++;
	}
}

int				ft_draw(t_app *a)
{
	a->img = mlx_new_image(a->win, WIN_W, WIN_H);
	a->img_data = mlx_get_data_addr(a->img, &a->n[0], &a->n[1], &a->n[2]);
	if (a->startscreen == 0)
	{
		if (a->life > 0 && a->screen_win == 0)
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
			ft_info(a);
		}
		else
			game_over(a);
	}
	else
		startscreen_draw(a);
	mlx_destroy_image(a->mlx, a->img);
	mlx_do_sync(a->mlx);
	return (0);
}
