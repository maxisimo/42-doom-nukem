/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:54:43 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/08 12:01:39 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

static void	texture_load(t_map *map)
{
	bmp_loadfile(&map->textures[0], "../textures/colorstone.bmp");
	bmp_loadfile(&map->textures[1], "../textures/greystone.bmp");
	bmp_loadfile(&map->textures[2], "../textures/wood.bmp");
	bmp_loadfile(&map->textures[3], "../textures/redbrick.bmp");
	bmp_loadfile(&map->textures[4], "../textures/purplestone.bmp");
	bmp_loadfile(&map->textures[5], "../textures/mossy.bmp");
	bmp_loadfile(&map->textures[6], "../textures/window.bmp");
	bmp_loadfile(&map->textures[7], "../textures/door1.bmp");
	bmp_loadfile(&map->textures[8], "../textures/door2.bmp");
	bmp_loadfile(&map->textures[9], "../sprites/zombie1.bmp");
	bmp_loadfile(&map->textures[10], "../sprites/barril.bmp");
	bmp_loadfile(&map->textures[11], "../sprites/pillar.bmp");
	bmp_loadfile(&map->textures[12], "../sprites/piece1.bmp");
}

void		error(void)
{
	ft_putendl("usage: ./map_generator newfile.w3d create");
	ft_putendl("                 or                   ");
	ft_putendl("usage: ./map_generator filename.w3d edit");
}

void		is_edit(char *s, t_map *map)
{
	map->edit = 1;
	map->name = s;
	map->i = 1;
	map->player = 0;
	init(map);
}

void		is_create(char *s, t_map *map)
{
	map->size = 40;
	map->bloc = 1280 / map->size;
	map->size *= map->bloc;
	map->name = s;
	map->i = 1;
	map->player = 0;
	init_tab(map);
}

void		start(t_map *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 1280 + 700, 1280, map->name);
	map->img = mlx_new_image(map->mlx, 1280 + 700, 1280);
	map->img_ptr = mlx_get_data_addr(map->img,
			&map->bpp, &map->sl, &map->endian);
	texture_load(map);
	draw_map(map);
}
