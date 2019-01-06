/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:07:49 by lchappon          #+#    #+#             */
/*   Updated: 2019/01/06 21:41:24 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include <stdio.h>

void		put_pxl_to_img(t_app *a, int x, int y, int color)
{
	if (x < WIN_W && y < WIN_H)
	{
		ft_memcpy(a->img_data + 4 * WIN_W * y + x * 4,
			&color, sizeof(int));
	}
}

static int	check_map(t_app *a, int x, int y)
{
	t_color	c1;

	c1.r = 25;
	c1.g = 45;
	c1.b = 145;
	if (a->map[x][y] >= 1)
		return (ft_rgb_to_hex(c1));
	return (0xFFFFFF);
}

void		draw_player(t_app *a)
{
	t_circle c;

	c.i = -1;
	while (++c.i < 5)
	{
		c.x = 0;
		c.y = c.i;
		c.d = 5 - 4 * c.i;
		c.xc = 105;
		c.yc = 105;
		while (c.x <= c.y)
			ft_put_circle_to_img(a, &c);
	}
}

static void	draw_rectangle(t_app *a)
{
	int		x;
	int		y;

	x = 6;
	while (x < 222)
	{
		y = 6;
		while (y < 222)
		{
			if ((x >= 6 && x < 8) || (x > 218 && x <= 222))
				put_pxl_to_img(a, x, y, 0xFFFFFF);
			if ((y >= 6 && y < 8) || (y > 218 && y <= 222))
				put_pxl_to_img(a, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}

void		draw_minimap(t_app *a)
{
	int		x;
	int		y;
	int		block;
	int		color;
	t_coord	tmp;

	x = 8;
	block = 30;
	draw_rectangle(a);
	while (++x < 218)
	{
		y = 8;
		while (++y < 218)
		{
			color = 0;
			tmp.x = (x / block) + a->pos.x - 3;
			tmp.y = (y / block) + a->pos.y - 3;
			if (tmp.x >= 0 && tmp.y >= 0 && tmp.x < a->map_size.x
					&& tmp.y < a->map_size.y)
				color = check_map(a, tmp.x, tmp.y);
			if (color == 0xFFFFFF)
				put_pxl_to_img(a, x, y, color);
		}
	}
}
