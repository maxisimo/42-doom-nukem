/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:16:44 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/15 19:12:09 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

static void	draw_infos(t_map *map)
{
	mlx_string_put(map->mlx, map->win, 1310, 500, 0xFFFFFF, TIP1);
	mlx_string_put(map->mlx, map->win, 1310, 550, 0xFFFFFF, TIP2);
	mlx_string_put(map->mlx, map->win, 1310, 600, 0xFFFFFF, TIP3);
	mlx_string_put(map->mlx, map->win, 1310, 650, 0xFFFFFF, TIP4);
	mlx_string_put(map->mlx, map->win, 1310, 700, 0xFFFFFF, TIP5);
}

static void	choose_color(t_map *map, int v, int x, int y)
{
	int			c;
	t_bmp		t;

	c = 0;
	t = map->textures[v - 1];
	if (v == -1)
		c = 0xFF4242;
	else if (v == 0)
		c = 0x000000;
	else if (v > 0)
	{
		c = ft_rgb_to_hex(get_pixel_color(&t, (x * 2) % t.width,
		(y * 2) % t.height));
	}
	put_px_to_img(map, x, y, c);
}

static void	draw_map(t_map *map)
{
	int		x;
	int		y;
	int		v;

	x = 0;
	while (x < map->size)
	{
		y = 0;
		while (y < map->size)
		{
			v = map->map[(y - 1) / map->bloc][(x - 1) / map->bloc];
			choose_color(map, v, x, y);
			y++;
		}
		x++;
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
				put_px_to_img(map, x + 1, y + 1, 0xFFFFFF);
			if (y == 1280 - 1)
				put_px_to_img(map, x, y, 0xFFFFFF);
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
	map->i > 0 ? map->textures[map->i - 1].scale = 2 : 0;
	map->i > 0 ? ft_put_bmp(map, map->textures[map->i - 1], 1500, 900) : 0;
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
	draw_infos(map);
	mlx_destroy_image(map->mlx, map->img);
	mlx_do_sync(map->mlx);
	return (0);
}
