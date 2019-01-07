/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 21:57:36 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/07 17:48:45 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

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
	{
		printf("%d %d %d\n", map->textures[map->i - 1].height, x, y);
		ft_put_bmp(map, map->textures[map->i - 1], 0, 0);
	}
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
