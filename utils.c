/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:09:00 by lchappon          #+#    #+#             */
/*   Updated: 2019/01/16 17:04:40 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		ft_rgb_to_hex(t_color c)
{
	return (((c.r & 0xff) << 16) + ((c.g & 0xff) << 8) + (c.b & 0xff));
}

void	ft_put_pxl_to_img(t_app *a, t_color c, int x, int y)
{
	int i;

	if (x < WIN_W && y < WIN_H && x >= 0 && y >= 0)
	{
		i = (x + (y * WIN_W)) * 4;
		a->img_data[i] = (char)c.b;
		a->img_data[i + 1] = (char)c.g;
		a->img_data[i + 2] = (char)c.r;
		if (a->life2 != a->life)
			a->img_data[i + 3] = 0xAC;
	}
}

void	ft_put_circle_to_img(t_app *a, t_circle *c)
{
	put_pxl_to_img(a, c->xc + c->x, c->yc - c->y, 0xFF0000);
	put_pxl_to_img(a, c->xc - c->x, c->yc - c->y, 0xFF0000);
	put_pxl_to_img(a, c->xc + c->x, c->yc + c->y, 0xFF0000);
	put_pxl_to_img(a, c->xc - c->x, c->yc + c->y, 0xFF0000);
	put_pxl_to_img(a, c->xc + c->y, c->yc - c->x, 0xFF0000);
	put_pxl_to_img(a, c->xc - c->y, c->yc - c->x, 0xFF0000);
	put_pxl_to_img(a, c->xc + c->y, c->yc + c->x, 0xFF0000);
	put_pxl_to_img(a, c->xc - c->y, c->yc + c->x, 0xFF0000);
	if (c->d > 0)
	{
		c->y--;
		c->d -= 8 * c->y;
	}
	c->x++;
	c->d = c->d + 8 * c->x + 4;
}

void	ft_put_bmp_to_img(t_app *a, t_bmp bmp, int x, int y)
{
	t_coord p;
	t_color	c;
	t_coord tmp;

	p.x = 0;
	p.y = 0;
	while (p.y < bmp.height * bmp.scale)
	{
		p.x = 0;
		while (p.x < bmp.width * bmp.scale)
		{
			c = get_pixel_color(&bmp, p.x / bmp.scale, p.y / bmp.scale);
			tmp.x = x + p.x;
			tmp.y = y + p.y;
			if (ft_rgb_to_hex(c) != 0xB80087 && tmp.x > 0 && tmp.y < WIN_W)
				ft_put_pxl_to_img(a, c, tmp.x, tmp.y);
			p.x++;
		}
		p.y++;
	}
}

void	ft_choose_color(int x, int start, t_app *a)
{
	t_color c1;

	if (a->texnum >= DOOR2)
		a->texnum = DOOR1;
	if (a->texy < 0 && a->texnum == DOOR1)
		a->texnum = DOOR2;
	ft_door_side(a);
	if (a->poster == 1)
		ft_poster(a);
	if (a->texy < 0)
		a->texy += a->textures[a->texnum].height;
	c1 = get_pixel_color(&a->textures[a->texnum], a->texx, a->texy);
	if (a->c == 0)
		ft_apply_shadow_to_color(&c1, a->wall.clr_intensity);
	ft_put_pxl_to_img(a, c1, x, start);
}
