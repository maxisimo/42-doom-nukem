/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:16:44 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/04 15:56:07 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

static void	put_px_to_img(t_map *map, int x, int y, int color)
{
	if (x < map->size && y < map->size && x >= 0 && y >= 0)
	{
		color = mlx_get_color_value(map->mlx, color);
		ft_memcpy(map->img_ptr + 4 * map->size * y + x * 4,
				&color, sizeof(int));
	}
}

static void	ft_put_bmp(t_map *map, t_bmp bmp, int x, int y)
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

static void	choose_color(int x, int y, t_map *map)
{
	int		clr;
	
	clr = (map->map[map->y][map->x] == 0) ? 0 : 0xFF4242;
	if (map->map[map->y][map->x] <= 0)
	{
		map->tempx = x;
		while (map->tempx < x + map->bloc - 1)
		{
			map->tempy = y;
			while (map->tempy < y + map->bloc - 1)
			{
				put_px_to_img(map, map->tempx, map->tempy, clr);
				map->tempy++;
			}
			map->tempx++;
		}
	}
	else
		ft_put_bmp(map, map->textures[map->i - 1], x, y);
}


void		infos(t_map *map)
{
	mlx_string_put(map->mlx, map->win, 1310, 100, 0xFFFFFF, "Press 'tab' to change texture");
	mlx_string_put(map->mlx, map->win, 1310, 200, 0xFFFFFF, "Press 'esc' or 's' to save and quit");
	mlx_string_put(map->mlx, map->win, 1310, 300, 0xFFFFFF, "Press 'P' to activate/desactivate the player position");
	mlx_string_put(map->mlx, map->win, 1310, 400, 0xFFFFFF, "Press the left mouse button to put a wall / player position");
	mlx_string_put(map->mlx, map->win, 1310, 500, 0xFFFFFF, "Press the right mouse button to take off a wall / player position");
}


void		put_color2(int x, int y, t_map *map)
{
	map->temp2x = 0;
	while (x < map->size)
	{
		y = 0;
		map->temp2y = 0;
		while (y < map->size)
		{
			map->x = x / map->bloc;
			map->y = y / map->bloc;
			map->i = map->map[map->temp2y][map->temp2x];
	        choose_color(x, y, map);
			y += map->bloc;
			map->temp2y++;
		}
		x += map->bloc;
		map->temp2x++;
	}
}

void		put_color(int x, int y, t_map *map)
{
	map->x = x / map->bloc;
	map->y = y / map->bloc;
	map->tempx = (map->x == 0) ? 1 : map->x * map->bloc;
    map->tempy = (map->y == 0) ? 0 : map->y * map->bloc;
	fill_tab(map->x, map->y, map->i, map);
	choose_color(map->tempx, map->tempy, map);
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
