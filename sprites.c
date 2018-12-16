/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:54:23 by thbernar          #+#    #+#             */
/*   Updated: 2018/12/16 15:41:23 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	sprites_load(t_app *a)
{
	a->spr_num = 7;
	bmp_loadfile(&a->sprites[2], "sprites/zombie1.bmp");
	bmp_loadfile(&a->weapon.img, "sprites/ak47.bmp");
	bmp_loadfile(&a->weapon.scope, "sprites/scope.bmp");
	bmp_loadfile(&a->startscreentxt, "sprites/zombie1.bmp");
	a->sprites[2].p.x = 2.5;
	a->sprites[2].p.y = 2.5;
}

void	sort_sprites(t_app *a)
{
	int		i;
	int		n;
	int		new;
	t_bmp	tmp;

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

void	sprites_init(t_app *a, t_spr *s, t_coord_d pos)
{
	s->spr_x = pos.y - a->pos.y;
	s->spr_y = pos.x - a->pos.x;
	s->invdet = 1.0 / (a->cam.plane.x * a->cam.dir.y -
			a->cam.dir.x * a->cam.plane.y);
	s->change_x = s->invdet * (a->cam.dir.y * s->spr_x -
			a->cam.dir.x * s->spr_y);
	s->change_y = s->invdet * (-a->cam.plane.y * s->spr_x +
			a->cam.plane.x * s->spr_y);
	s->screenx = (int)((WIN_W / 2) * (1 + s->change_x / s->change_y));
	s->height = abs((int)(WIN_H / (s->change_y)));
	s->start_y = -s->height / 2;
	s->start_y -= s->start_y * a->move.v;
	s->start_y += WIN_H / 2 + a->rot.v;
	s->start_y = (s->start_y < 0) ? 0 : s->start_y;
	s->end_y = s->height / 2;
	s->end_y += s->end_y * a->move.v;
	s->end_y += WIN_H / 2 + a->rot.v;
	s->end_y = (s->end_y > WIN_H) ? WIN_H - 1 : s->end_y;
	s->width = abs((int)(WIN_H / (s->change_y)));
	s->start_x = -s->width / 2 + s->screenx;
	s->start_x = (s->start_x < 0) ? 0 : s->start_x;
	s->end_x = s->width / 2 + s->screenx;
	s->end_x = (s->end_x > WIN_W) ? WIN_W - 1 : s->end_x;
	s->stripe = s->start_x;
}

void	put_sprite(t_app *a, t_spr *s)
{
	t_color		c;

	while (s->stripe < s->end_x)
	{
		s->texx = (int)((s->stripe - (-s->width / 2 + s->screenx))
				* s->img->width / s->width);
		if (s->change_y > 0 && s->stripe > 0 && s->stripe < WIN_W &&
				s->change_y < a->zbuffer[s->stripe])
		{
			s->y = s->start_y - 1;
			while (s->y < s->end_y)
			{
				s->texy = ((s->y - WIN_H / 2 + (s->height / 2)
							* (-a->move.v + 1) - a->rot.v)
							* s->img->height) / s->height;
				c = get_pixel_color(s->img, s->texx, s->texy);
				if (s->dist < 20 && c.r != 0 && c.g != 0 && c.b != 0)
					ft_put_pxl_to_img(a, c, s->stripe, s->y);
				s->y++;
			}
		}
		s->stripe++;
	}
}

void	sprites_draw(t_app *a, t_spr s, t_coord_d pos)
{
	int	c;
	int	b;

	c = a->pos.x - pos.x;
	b = a->pos.y - pos.y;
	s.dist = c * c + b * b;
	sprites_init(a, &s, pos);
	put_sprite(a, &s);
}
