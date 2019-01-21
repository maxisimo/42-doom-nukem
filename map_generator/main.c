/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:39:00 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/16 17:31:50 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

static int	is_extension_valid(char *fname)
{
	if (ft_strncmp(ft_strrev(fname), "d3w.", 4) == 0)
	{
		free(fname);
		return (1);
	}
	else
	{
		free(fname);
		return (0);
	}
}

static void	texture_load(t_map *map)
{
	bmp_loadfile(&map->textures[0], "textures/colorstone.bmp", 64, 64);
	bmp_loadfile(&map->textures[1], "textures/greystone.bmp", 64, 64);
	bmp_loadfile(&map->textures[2], "textures/wood.bmp", 64, 64);
	bmp_loadfile(&map->textures[3], "textures/redbrick.bmp", 64, 64);
	bmp_loadfile(&map->textures[4], "textures/purplestone.bmp", 64, 64);
	bmp_loadfile(&map->textures[5], "textures/mossy.bmp", 64, 64);
	bmp_loadfile(&map->textures[6], "textures/window.bmp", 64, 64);
	bmp_loadfile(&map->textures[7], "textures/door1-5.bmp", 64, 64);
	bmp_loadfile(&map->textures[8], "textures/door1.bmp", 64, 64);
	bmp_loadfile(&map->textures[9], "sprites/zombie1.bmp", 64, 64);
	bmp_loadfile(&map->textures[10], "sprites/barril.bmp", 64, 64);
	bmp_loadfile(&map->textures[11], "sprites/pillar.bmp", 64, 64);
	bmp_loadfile(&map->textures[12], "sprites/skull1.bmp", 64, 64);
}

int			main(int ac, char **av)
{
	t_map	map;

	if (ac == 2 && is_extension_valid(ft_strdup(av[1])) == 1)
	{
		map.name = av[1];
		init(&map);
		texture_load(&map);
		map.mlx = mlx_init();
		map.win = mlx_new_window(map.mlx, 1980, 1280, map.name);
		draw(&map);
		mlx_key_hook(map.win, key_hook, &map);
		mlx_mouse_hook(map.win, mouse_hook, &map);
		mlx_loop(map.mlx);
	}
	else
		ft_putendl("usage: ./map-generator <file.w3d>");
	return (0);
}
