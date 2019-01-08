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

void		infos(t_map *map)
{
	mlx_string_put(map->mlx, map->win, 1310, 500, 0xFFFFFF, TIP1);
	mlx_string_put(map->mlx, map->win, 1310, 550, 0xFFFFFF, TIP2);
	mlx_string_put(map->mlx, map->win, 1310, 600, 0xFFFFFF, TIP3);
	mlx_string_put(map->mlx, map->win, 1310, 650, 0xFFFFFF, TIP4);
	mlx_string_put(map->mlx, map->win, 1310, 700, 0xFFFFFF, TIP5);
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