/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:54:23 by thbernar          #+#    #+#             */
/*   Updated: 2019/01/16 17:33:12 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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

void		mlx_win_init(t_app *app)
{
	app->mlx = mlx_init();
	app->win = mlx_new_window(app->mlx, WIN_W, WIN_H, "doom-nukem");
	mlx_hook(app->win, 2, (1L << 0), ft_key_press, app);
	mlx_hook(app->win, 3, (1L << 1), ft_key_release, app);
	mlx_mouse_hide();
	mlx_mouse_move(app->win, WIN_W / 2, WIN_H / 2);
	mlx_hook(app->win, 4, 0, ft_button_press, app);
	mlx_hook(app->win, 5, 0, ft_button_release, app);
	mlx_hook(app->win, 6, 0, ft_mouse_motion, app);
	mlx_hook(app->win, 17, (1L << 17), ft_close, app);
	mlx_loop_hook(app->mlx, ft_draw, app);
	mlx_loop(app->mlx);
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
		app.move.s = 0.07;
		app.startscreen = 1;
		ft_app_init(&app);
		sprites_load(&app);
		bmp_loadfile(&app.logo, "sprites/doomnukemlogo.bmp", 812, 192);
		system("/usr/bin/afplay -q 1 ./songs/halloween.mp3&");
		mlx_win_init(&app);
	}
	else
		ft_putstr("usage: ./doom-nukem <file.w3d>\n");
	return (0);
}
