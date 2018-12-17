/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:16:44 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/17 19:11:19 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

static void	put_px_to_img(t_map *map, int x, int y, int color)
{
	if (x < map->width && y < map->height && x >= 0 && y >= 0)
	{
		color = mlx_get_color_value(map->mlx, color);
		ft_memcpy(map->img_ptr + 4 * map->width * y + x * 4,
				&color, sizeof(int));
	}
}

static void	choose_color(int x, int y, t_map *map)
{
	if (map->map[map->y][map->x] < 0)
		put_px_to_img(map, x, y, 0xFF4242);
	else if (map->map[map->y][map->x] == 0)
		put_px_to_img(map, x, y, 0);
	else
		put_px_to_img(map, x, y, 0xFFFFFF);
}

void		draw_grill(int x, int y, t_map *map)
{
	int		color;

	color = (map->ac == 2) ? 0 : 0xFFFFFF;
	while (x < map->width)
	{
		y = map->height - 1;
		while (y >= 0)
		{
			if (x == 0 || y == map->height - 1)
				put_px_to_img(map, x, y, color);
			if (((x + 1) % map->bloc) == 0 || ((y + 1) % map->bloc) == 0)
				put_px_to_img(map, x, y, color);
			y--;
		}
		x++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
}

void		put_color2(int x, int y, t_map *map)
{
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			map->x = x / map->bloc;
			map->y = y / map->bloc;
			map->tempx = (map->x == 0) ? 1 : map->x * map->bloc;
			map->n = (map->x == 0) ? 3 : 2;
			map->temp2x = map->tempx;
			while (map->tempx <= map->temp2x + map->bloc - map->n)
			{
				map->tempy = (map->y == 0) ? 0 : map->y * map->bloc;
				map->temp2y = map->tempy;
				while (map->tempy <= map->temp2y + map->bloc - 2)
				{
					choose_color(map->tempx, map->tempy, map);
					map->tempy++;
				}
				map->tempx++;
			}
			mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
			y += map->bloc;
		}
		x += map->bloc;
	}
}

void		put_color(int x, int y, t_map *map)
{
	map->x = x / map->bloc;
	map->y = y / map->bloc;
	map->tempx = (map->x == 0) ? 1 : map->x * map->bloc;
	map->n = (map->x == 0) ? 3 : 2;
	map->temp2x = map->tempx;
	fill_tab(map->x, map->y, map->i, map);
	while (map->tempx <= map->temp2x + map->bloc - map->n)
	{
		map->tempy = (map->y == 0) ? 0 : map->y * map->bloc;
		map->temp2y = map->tempy;
		while (map->tempy <= map->temp2y + map->bloc - 2)
		{
			choose_color(map->tempx, map->tempy, map);
			map->tempy++;
		}
		map->tempx++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
}
