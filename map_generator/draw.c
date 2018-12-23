/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:16:44 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/23 15:08:29 by lchappon         ###   ########.fr       */
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

void	ft_put_bmp(t_map *map, t_bmp bmp, int x, int y)
{
	int		clr;
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
			if ((clr = ft_rgb_to_hex(c)) != 0xB80087 && tmp.x > 0 &&
					tmp.y < map->height)
				put_px_to_img(map, tmp.x, tmp.y, clr);
			p.x++;
		}
		p.y++;
	}
}

static void	choose_color(int x, int y, t_map *map)
{
	if (map->map[map->y][map->x] < 0)
		put_px_to_img(map, x, y, 0xFF4242);
	else if (map->map[map->y][map->x] == 0)
		put_px_to_img(map, x, y, 0);
	else
		ft_put_bmp(map, map->textures[map->i - 1], x, y);
}

void		put_color2(int x, int y, t_map *map)
{
	while (x < map->width)
	{
		while (y < map->height)
		{
	        choose_color(x, y, map);
			y += map->bloch;
		}
		x += map->blocw;
	}
}

void		put_color(int x, int y, t_map *map)
{
	map->x = x / map->blocw;
	map->y = y / map->bloch;
	map->tempx = (map->x == 0) ? 1 : map->x * map->blocw;
    map->tempy = (map->y == 0) ? 0 : map->y * map->bloch;
	fill_tab(map->tempx, map->tempy, map->i, map);
	choose_color(map->tempx, map->tempy, map);
}

void		draw_grill(int x, int y, t_map *map)
{
	int		color;

	color = 0xFFFFFF;
	while (x < map->width)
	{
		y = map->height - 1;
		while (y >= 0)
		{
			if (x == 0 || y == map->height - 1)
				put_px_to_img(map, x, y, color);
			if (((x + 1) % map->blocw) == 0 || ((y + 1) % map->bloch) == 0)
				put_px_to_img(map, x, y, color);
			y--;
		}
		x++;
	}
    if (map->ac == 2)
		put_color2(0, 0, map);
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
}
