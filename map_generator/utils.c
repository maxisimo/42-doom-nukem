/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:54:43 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/04 13:54:09 by maxisimo         ###   ########.fr       */
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
	ft_putendl("usage: ./map_generator newfilename create");
	ft_putendl("                 or                   ");
	ft_putendl("usage: ./map_generator filename edit");
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
	map->img = mlx_new_image(map->mlx, 1280, 1280);
	map->img_ptr = mlx_get_data_addr(map->img,
			&map->bpp, &map->sl, &map->endian);
	texture_load(map);
	infos(map);
	draw_map(0, 0, map);
}
