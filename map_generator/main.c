/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:39:00 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/07 18:24:36 by maxisimo         ###   ########.fr       */
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

static int	check(char *fname)
{
	if (ft_strncmp(ft_strrev(fname), "d3w.", 4) == 0)
		return (1);
	else if (ft_strncmp(ft_strrev(fname), "edit", 4) == 0)
		return (2);
	else if (ft_strncmp(ft_strrev(fname), "etaerc", 6) == 0)
		return (3);
	else
		return (0);
}

int			main(int ac, char **av)
{
	t_map	map;

	if (ac == 3 && check(ft_strdup(av[1])) == 1)
	{
		ft_bzero(&map, sizeof(t_map));
		if (check(ft_strdup(av[2])) == 2)
			is_edit(av[1], &map);
		else if (check(ft_strdup(av[2])) == 3)
			is_create(av[1], &map);
		else
		{
			error();
			return (0);
		}
		map.mlx = mlx_init();
		map.win = mlx_new_window(map.mlx, 1980, 1280, map.name);
		texture_load(&map);
		mlx_key_hook(map.win, key_hook, &map);
		mlx_mouse_hook(map.win, mouse_hook, &map);
		mlx_loop_hook(map.mlx, &draw, &map);
		mlx_loop(map.mlx);
	}
	else 
		error();
	return (0);
}
