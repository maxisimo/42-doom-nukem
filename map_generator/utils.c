/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:54:43 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/16 14:26:08 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

void	put_px_to_img(t_map *map, int x, int y, int color)
{
	if (x < 1920 && y < map->size && x >= 0 && y >= 0)
	{
		color = mlx_get_color_value(map->mlx, color);
		ft_memcpy(map->img_ptr + 4 * (map->size + 700) * y + x * 4,
				&color, sizeof(int));
	}
}

void	ft_put_bmp(t_map *a, t_bmp bmp, int x, int y)
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
				put_px_to_img(a, tmp.x, tmp.y, ft_rgb_to_hex(c));
			p.x++;
		}
		p.y++;
	}
}
