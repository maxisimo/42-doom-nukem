/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:54:23 by thbernar          #+#    #+#             */
/*   Updated: 2018/12/13 12:55:21 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	sprites_load(t_app *a)
{
	a->spr_num = 7;
	bmp_loadfile(&a->sprites[2], "sprites/zombie1.bmp");
	bmp_loadfile(&a->sprites[3], "sprites/zombie1.bmp");
	bmp_loadfile(&a->sprites[4], "sprites/zombie1.bmp");
	bmp_loadfile(&a->sprites[5], "sprites/zombie1.bmp");
	bmp_loadfile(&a->sprites[6], "sprites/zombie1.bmp");
	bmp_loadfile(&a->sprites[7], "sprites/zombie1.bmp");
	bmp_loadfile(&a->sprites[8], "sprites/zombie1.bmp");
	bmp_loadfile(&a->weapon.sprite, "sprites/ak47.bmp");
	a->sprites[2].p.x = 2.5;
	a->sprites[2].p.y = 2.5;
}

void	sprites_get_coord(t_app *a, int i)
{
	int		x;
	int		y;
	y = 0;
	while (y < a->map_size.y)
	{
		x = 0;
		while (x < a->map_size.x)
		{
			if (a->map[x][y] == 9)
			{
				a->sprites[i].p.y = (double)y + 0.5;
				a->sprites[i].p.x = (double)x + 0.5;
			}
			x++;
		}
		y++;
	}
}

void	sort_sprites(t_app *a)
{
	int i;
	int n;
	int new;
	t_bmp tmp;

	n = a->spr_num;
	new = 1;
	while (new != 0)
	{
		new = 0;
		i = 0;
		while (++i <= n - 1)
		{
			if (a->sprites[i].dist - a->sprites[i - 1].dist > 0.1)
			{
				tmp = a->sprites[i];
				a->sprites[i] = a->sprites[i - 1];
				a->sprites[i - 1] = tmp;
				new = 1;
			}
		}
	}
}

void	sprites_init(t_app *a, t_spr *s, int i)
{
	t_coord_d	rel;
	t_coord_d	p1;
	t_coord_d	p2;

	p1 = a->sprites[i].p;
	p2 = a->pos;
	rel.x = p1.x - p2.x;
	rel.y = p1.y - p2.y;
	s->spr_x = a->sprites[i].p.y - a->pos.y;
	s->spr_y = a->sprites[i].p.x - a->pos.x;
	s->invdet = 1.0 / (a->cam.plane.x * a->cam.dir.y - a->cam.dir.x * a->cam.plane.y);
	s->change_x = s->invdet * (a->cam.dir.y * s->spr_x - a->cam.dir.x * s->spr_y);
	s->change_y = s->invdet * (-a->cam.plane.y * s->spr_x + a->cam.plane.x * s->spr_y);
	s->screenx = (int)((WIN_W / 2) * (1 + s->change_x / s->change_y));
	s->height = abs((int)(WIN_H / (s->change_y)));
	s->start_y = -s->height / 2 + WIN_H / 2;
	s->start_y = (s->start_y < 0) ? 0 : s->start_y;
	s->end_y = s->height / 2 + WIN_H / 2;
	s->end_y = (s->end_y > WIN_H) ? WIN_H - 1 : s->end_y;
	s->width = abs((int)(WIN_H / (s->change_y)));
	s->start_x = -s->width / 2 + s->screenx;
	s->start_x = (s->start_x < 0) ? 0 : s->start_x;
	s->end_x = s->width / 2 + s->screenx;
	s->end_x = (s->end_x > WIN_W) ? WIN_W - 1 : s->end_x;
	s->stripe = s->start_x;
}

void	put_sprite(t_app *a, t_spr *s, int i)
{
	t_color		color;

	while (s->stripe < s->end_x)
	{
		s->texx = (int)((s->stripe - (-s->width / 2 + s->screenx))
				* a->sprites[i].width / s->width);
		if (s->change_y > 0 && s->stripe > 0 && s->stripe < WIN_W && s->change_y < a->zbuffer[s->stripe])
		{
			s->y = s->start_y - 1;
			while (s->y < s->end_y)
			{
				s->d = (s->y) * 2 - WIN_H + s->height;
				s->texy = ((s->d * a->sprites[i].height) / s->height) / 2;
				color = get_pixel_color(&a->sprites[i], s->texx, s->texy);
				ft_apply_shadow_to_spr(&color, a->sprites[i].dist);
				s->clr = ft_rgb_to_hex(color);
				if (s->clr != 0)
					ft_memcpy(a->img_data + 4 * WIN_W * s->y + s->stripe * 4,
							&s->clr, sizeof(int));
				s->y++;
			}
		}
		s->stripe++;
	}
}

void	sprites_draw(t_app *a)
{
	int			i;
	t_spr		s;

	i = -1;
	while (++i < a->spr_num)
	{
		a->sprites[i].dist = (a->pos.x - a->sprites[i].p.x) *
			(a->pos.x - a->sprites[i].p.x) + (a->pos.y - a->sprites[i].p.y) *
				(a->pos.y - a->sprites[i].p.y);
	}
	sort_sprites(a);
	i = -1;
	while (++i < a->spr_num)
	{
		sprites_init(a, &s, i);
		put_sprite(a, &s, i);
	}
}
