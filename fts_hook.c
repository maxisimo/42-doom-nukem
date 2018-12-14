/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 11:15:41 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/14 14:24:35 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int			ft_mouse_motion(int x, int y, t_app *app)
{
	mlx_mouse_hide();
	app->rot.s = -0.002 * (x - WIN_W / 2);
	mlx_mouse_move(app->win, WIN_W / 2, y);
	if (y >= 0 && y <= WIN_H)
		app->rot.v = -(y - WIN_H / 2);
	if (y < 0)
		mlx_mouse_move(app->win, x, 0);
	if (y > WIN_H)
		mlx_mouse_move(app->win, x, WIN_H);
	return (0);
}

int			ft_key_press(int key, t_app *app)
{
	app->startscreen = 0;
	if (key == 13)
		app->move.up = 1;
	else if (key == 1)
		app->move.down = 1;
	else if (key == 2)
		app->move.right = 1;
	else if (key == 0)
		app->move.left = 1;
	else if (key == 123)
		app->rot.left = 1;
	else if (key == 124)
		app->rot.right = 1;
	else if (key == 125)
		app->rot.down = 1;
	else if (key == 126)
		app->rot.up = 1;
	else if (key == 12)
	{
		app->weapon.fire_count = 0;
		app->weapon.is_fired = 1;
	}
	ft_key_press2(key, app);
	return (0);
}

int			ft_key_press2(int key, t_app *app)
{
	if (key == 12)
		app->weapon.is_fired = 1;
	else if (key == 8)
		app->c = (app->c == 1) ? 0 : 1;
	else if (key == 18)
		app->is_weapon = 1;
	else if (key == 19)
		app->is_weapon = 0;
	else if (key == 257)
		app->speed = 1;
	else if (key == 53)
		exit(0);
	return (0);
}

int			ft_key_release(int key, t_app *app)
{
	if (key == 13)
		app->move.up = 0;
	else if (key == 1)
		app->move.down = 0;
	else if (key == 2)
		app->move.right = 0;
	else if (key == 0)
		app->move.left = 0;
	else if (key == 123)
		app->rot.left = 0;
	else if (key == 124)
		app->rot.right = 0;
	else if (key == 125)
		app->rot.down = 0;
	else if (key == 126)
		app->rot.up = 0;
	else if (key == 12)
		app->weapon.is_fired = 0;
	else if (key == 257)
		app->speed = 0;
	return (0);
}
