/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:16:44 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/10 18:31:45 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

void		put_px_to_img(t_map *map, int x, int y, int color)
{
	if (x < 1920 && y < map->size && x >= 0 && y >= 0)
	{
		color = mlx_get_color_value(map->mlx, color);
		ft_memcpy(map->img_ptr + 4 * (map->size + 700) * y + x * 4,
				&color, sizeof(int));
	}
}

static void	draw_lines(t_map *map)
{
	int		x;
	int		y;

	x = 0;
	while (x < map->size)
	{
		y = 0;
		while (y < map->size)
		{
			if (x == 0 || y == 0)
				put_px_to_img(map, x, y, 0xFFFFFF);
			if ((x + 1) % map->bloc == 0 || (y + 1) % map->bloc == 0)
				put_px_to_img(map, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}

static void	choose_color(int x, int y, int color, t_map *map)
{
	if (map->map[map->tmp.y][map->tmp.x] == -1)
		put_px_to_img(map, x, y, 0xFF4242);
	else if (map->map[map->tmp.y][map->tmp.x] == 0)
		put_px_to_img(map, x, y, 0x000000);
	else if (map->map[map->tmp.y][map->tmp.x] > 0)
		put_px_to_img(map, x, y, color);
}

static void	draw_map(t_map *map)
{
	int		color;
	int		x;
	int		y;
	t_color	c1;

	x = 0;
	while (x < map->size)
	{
		y = 0;
		while (y < map->size)
		{
			map->tmp.x = x / map->bloc;
			map->tmp.y = y / map->bloc;
			c1 = get_pixel_color(&map->textures[map->map[map->tmp.y]
				[map->tmp.x]], (x % 64) * 2, (y % 64) * 2);
			color = ft_rgb_to_hex(c1);
			choose_color(x, y, color, map);
			y++;
		}
		x++;
	}
}

int			draw(t_map *map)
{
	int	p[3];

	map->img = mlx_new_image(map->mlx, 1980, 1280);
	map->img_ptr = mlx_get_data_addr(map->img, &p[0], &p[1], &p[2]);
	draw_map(map);
	draw_lines(map);
	map->textures[map->i].scale = 2;
	map->i > 0 ? ft_put_bmp(map, map->textures[map->i], 1500, 900) : 0;
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
	infos(map);
	mlx_destroy_image(map->mlx, map->img);
	mlx_do_sync(map->mlx);
	return (0);
}
