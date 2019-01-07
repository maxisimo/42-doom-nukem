/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:16:44 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/07 18:13:28 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

void		put_px_to_img(t_map *map, int x, int y, int color)
{
	if (x < map->size && y < map->size && x >= 0 && y >= 0)
	{
		color = mlx_get_color_value(map->mlx, color);
		ft_memcpy(map->img_ptr + 4 * (map->size + 700) * y + x * 4,
				&color, sizeof(int));
	}
}

void		ft_put_bmp(t_map *map, t_bmp bmp, int x, int y)
{
	int		clr;
	t_coord p;
	t_color	c;
	t_coord tmp;

	p.x = 0;
	p.y = 0;
	while (p.y < bmp.size * bmp.scale)
	{
		p.x = 0;
		while (p.x < bmp.size * bmp.scale)
		{
			c = get_pixel_color(&bmp, p.x / bmp.scale, p.y / bmp.scale);
			tmp.x = x + p.x;
			tmp.y = y + p.y;
			if ((clr = ft_rgb_to_hex(c)) != 0xB80087 && tmp.x > 0 &&
					tmp.y < map->size)
				put_px_to_img(map, tmp.x, tmp.y, clr);
			p.x++;
		}
		p.y++;
	}
}

void		infos(t_map *map)
{
	mlx_string_put(map->mlx, map->win, 1310, 500, 0xFFFFFF, TIP1);
	mlx_string_put(map->mlx, map->win, 1310, 550, 0xFFFFFF, TIP2);
	mlx_string_put(map->mlx, map->win, 1310, 600, 0xFFFFFF, TIP3);
	mlx_string_put(map->mlx, map->win, 1310, 650, 0xFFFFFF, TIP4);
	mlx_string_put(map->mlx, map->win, 1310, 700, 0xFFFFFF, TIP5);
}

void		draw_map(int x, int y, t_map *map)
{
	int		color;

	color = 0xFFFFFF;
	while (x < map->size)
	{
		y = 0;
		while (y < map->size)
		{
			if (x == 0 || y == 0)
				put_px_to_img(map, x, y, color);
			if (((x + 1) % map->bloc) == 0 || ((y + 1) % map->bloc) == 0)
				put_px_to_img(map, x, y, color);
			y++;
		}
		x++;
	}
	if (map->edit == 1)
		put_color2(0, 0, map);
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
}
