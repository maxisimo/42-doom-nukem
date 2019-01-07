/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:39:00 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/07 18:16:14 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

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
		start(&map);
		mlx_hook(map.win, 2, (1L << 0), &key_hook, &map);
		mlx_mouse_hook(map.win, mouse_hook, &map);
		mlx_loop(map.mlx);
	}
	else
		error();
	return (0);
}
