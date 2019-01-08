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
	if (x < 1920 && y < map->size && x >= 0 && y >= 0)
	{
		color = mlx_get_color_value(map->mlx, color);
		ft_memcpy(map->img_ptr + 4 * (map->size + 700) * y + x * 4,
				&color, sizeof(int));
	}
}

void		draw_lines(t_map *map)
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

void		draw_map(t_map *map)
{
	int		color;
	int		x;
	int		y;
	t_coord	tmp;

	x = 0;
	color = 0xFFFFFF;
	while (x < map->size)
	{
		y = 0;
		while (y < map->size)
		{
			tmp.y = y / map->bloc;
			tmp.x = x / map->bloc;
			if (map->map[y / map->bloc][x / map->bloc] == -1)
				put_px_to_img(map, x, y, 0xFF4242);
			else if (map->map[y / map->bloc][x / map->bloc] == 0)
				put_px_to_img(map, x, y, 0x000000);
			else if (map->map[y / map->bloc][x / map->bloc] > 0)
				put_px_to_img(map, x, y, ft_rgb_to_hex(get_pixel_color(&map->textures[map->map[tmp.y][tmp.x]], (x % 64) * 2, (y % 64) * 2)));
			y++;
		}
		x++;
	}
}

int		draw(t_map *map)
{
	int	p[3];

	map->img = mlx_new_image(map->mlx, 1980, 1280);
	map->img_ptr = mlx_get_data_addr(map->img, &p[0], &p[1], &p[2]);
	draw_map(map);
	draw_lines(map);
	map->textures[map->i].scale = 2;
	ft_put_bmp(map, map->textures[map->i], WIN_W, 0);
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
	infos(map);
	mlx_destroy_image(map->mlx, map->img);
	mlx_do_sync(map->mlx);
	return (0);
}
