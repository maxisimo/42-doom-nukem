/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:54:23 by thbernar          #+#    #+#             */
/*   Updated: 2018/12/12 05:47:23 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static int	is_extension_valid(char *fname)
{
	if (ft_strncmp(ft_strrev(fname), "d3w.", 4) == 0)
		return (1);
	else
		return (0);
}

int			main(int ac, char **av)
{
	t_app	a;

	if (ac == 2 && is_extension_valid(ft_strdup(av[1])) == 1)
	{
		a.fname = av[1];
		a.dir_x = -1;
		a.plane_y = 0.66;
		a.ms = 0.07;
		ft_app_init(&a);
		sprites_load(&a);
		a.mlx = mlx_init();
		a.win = mlx_new_window(a.mlx, WIN_W, WIN_H, "Wolf3D");
		bmp_loadfile(&a.logo, "textures/logo.bmp");
		mlx_hook(a.win, 2, (1L << 0), ft_key_press, &a);
		mlx_hook(a.win, 3, (1L << 1), ft_key_release, &a);
		mlx_hook(a.win, 17, (1L << 17), ft_close, &a);
		mlx_loop_hook(a.mlx, ft_draw, &a);
		mlx_loop(a.mlx);
	}
	else
		ft_putstr("usage: ./wolf3d maps/*.w3d\n");
	return (0);
}
