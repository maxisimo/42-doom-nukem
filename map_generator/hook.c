/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:14:38 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/07 18:14:10 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

int			key_hook(int keycode, t_map *map)
{
	if (keycode == 35)
	{
		if (map->player == 1)
			map->player = 0;
		else
			map->player = 1;
	}
	else if (keycode == 48)
		map->i = (map->i < 1 || map->i > 5) ? 1 : map->i + 1;
	else if (keycode == 53)
		exit(0);
	else if (keycode == 1)
	{
		map_save(map);
		exit(0);
	}
	return (0);
}

int			mouse_hook(int mousecode, int x, int y, t_map *map)
{
	if (mousecode == 1)
		map->i = (map->player == 1) ? -1 : map->i;
	else if (mousecode == 2)
		map->i = 0;
	map->map[y / map->bloc][x / map->bloc] = map->i;
	return (0);
}
