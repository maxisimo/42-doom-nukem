/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:54:43 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/02 16:38:21 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

static void	texture_load(t_map *map)
{
	bmp_loadfile(&map->textures[0], "textures/bigdoor.bmp");
	bmp_loadfile(&map->textures[1], "textures/dude.bmp");
	bmp_loadfile(&map->textures[2], "textures/metal.bmp");
	bmp_loadfile(&map->textures[3], "textures/floor.bmp");
	bmp_loadfile(&map->textures[4], "textures/skulwall.bmp");
	bmp_loadfile(&map->textures[5], "textures/marbface.bmp");
	bmp_loadfile(&map->textures[6], "textures/skulwall2.bmp");
}

void		error(void)
{
	ft_putendl("usage: ./map_generator newfilename [width] [height]");
	ft_putendl("or");
	ft_putendl("usage: ./map_generator filename");
}

void		is_argc_2(char *s, t_map *map)
{
	map->ac = 2;
	map->name = s;
	map->i = 1;
	map->player = 0;
}

void		is_argc_4(char *s1, char *s2, char *s3, t_map *map)
{
	map->ac = 4;
	map->width = (abs(ft_atoi(s2)) > 55) ? 55 : abs(ft_atoi(s2));
	map->height = (abs(ft_atoi(s3)) > 55) ? 55 : abs(ft_atoi(s3));
	map->blocw = 1320 / map->width;
	map->bloch = 1320 / map->height;
	map->width *= map->blocw;
	map->height *= map->bloch;
	map->name = s1;
	map->i = 1;
	map->player = 0;
}

void		start(t_map *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 1320 + 700, 1320, map->name);
	map->img = mlx_new_image(map->mlx, 1320, 1320);
	map->img_ptr = mlx_get_data_addr(map->img,
			&map->bpp, &map->sl, &map->endian);
	texture_load(map);
	infos(map);
	draw_map(0, 0, map);
}
