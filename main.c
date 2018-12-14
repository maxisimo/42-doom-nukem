/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:54:23 by thbernar          #+#    #+#             */
/*   Updated: 2018/12/14 15:14:00 by maxisimo         ###   ########.fr       */
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
	t_app	app;

	if (ac == 2 && is_extension_valid(ft_strdup(av[1])) == 1)
	{
		ft_bzero(&app, sizeof(t_app));
		app.fname = av[1];
		app.cam.dir.x = -1;
		app.cam.plane.y = 0.66;
		app.ms = 0.07;
		ft_app_init(&app);
		sprites_load(&app);
		app.mlx = mlx_init();
		app.win = mlx_new_window(app.mlx, WIN_W, WIN_H, "doom-nukem");
		bmp_loadfile(&app.logo, "sprites/dukenukemlogo.bmp");
		mlx_hook(app.win, 2, (1L << 0), ft_key_press, &app);
		mlx_hook(app.win, 3, (1L << 1), ft_key_release, &app);
		mlx_hook(app.win, 17, (1L << 17), ft_close, &app);
		mlx_loop_hook(app.mlx, ft_draw, &app);
		mlx_loop(app.mlx);
	}
	else
		ft_putstr("usage: ./doom-nukem maps/*.w3d\n");
	return (0);
}
