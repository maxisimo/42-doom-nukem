/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:39:00 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/18 16:00:46 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

static int	is_extension_valid(char *fname)
{
	if (ft_strncmp(ft_strrev(fname), "d3w.", 4) == 0)
		return (1);
	else
		return (0);
}

int		main(int ac, char **av)
{
	t_map	map;

	if (ac == 4 && ft_strisnumeric(av[2]) == 1 && ft_strisnumeric(av[3]) == 1)
	{
		is_argc_4(av[1], av[2], av[3], &map);
*		init_tab(&map);
		start(&map);
		mlx_hook(map.win, 2, (1L << 0), &key_hook, &map);
		mlx_mouse_hook(map.win, mouse_hook, &map);
		mlx_loop(map.mlx);
	}
	else if (ac == 2 && is_extension_valid(ft_strdup(av[1])) == 1)
	{
		is_argc_2(av[1], &map);
		init(&map);
		start(&map);
		mlx_hook(map.win, 2, (1L << 0), &key_hook, &map);
		mlx_mouse_hook(map.win, mouse_hook, &map);
		mlx_loop(map.mlx);
	}
	else
		error();
	return (0);
}
