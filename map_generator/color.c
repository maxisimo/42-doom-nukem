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
