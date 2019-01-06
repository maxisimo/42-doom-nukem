/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 21:20:47 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/06 21:21:06 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			ft_mouse_motion(int x, int y, t_app *app)
{
	mlx_mouse_hide();
	app->rot.s = -0.002 * (x - WIN_W / 2);
	app->rot.v -= (y - WIN_H / 2);
	if (app->rot.v < -WIN_H / 2)
		app->rot.v = -WIN_H / 2;
	if (app->rot.v > WIN_H / 2)
		app->rot.v = WIN_H / 2;
	mlx_mouse_move(app->win, WIN_W / 2, WIN_H / 2);
	return (0);
}

int			ft_button_release(int button, int x, int y, t_app *app)
{
	if (x >= 0 && x <= WIN_W && y >= 0 && y <= WIN_H)
	{
		if (button == 1)
			app->weapon.is_fired = 0;
	}
	return (0);
}

int			ft_button_press(int button, int x, int y, t_app *app)
{
	if (x >= 0 && x <= WIN_W && y >= 0 && y <= WIN_H)
	{
		if (button == 1)
			app->weapon.is_fired = 1;
	}
	return (0);
}
