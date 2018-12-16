/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:07:26 by lchappon          #+#    #+#             */
/*   Updated: 2018/12/16 16:07:28 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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

int			ft_motion(int key, t_app *app, int value)
{
	if (key == 13)
		app->move.up = value;
	else if (key == 1)
		app->move.down = value;
	else if (key == 2)
		app->move.right = value;
	else if (key == 0)
		app->move.left = value;
	else if (key == 126)
		app->rot.up = value;
	else if (key == 125)
		app->rot.down = value;
	else if (key == 124)
		app->rot.right = value;
	else if (key == 123)
		app->rot.left = value;
	return (0);
}

int			ft_key_release(int key, t_app *app)
{
	ft_motion(key, app, 0);
	if (key == 12)
		app->weapon.is_fired = 0;
	else if (key == 257)
		app->speed = 0;
	else if (key == 49)
		app->jump = 0;
	else if (key == 8)
		app->crouch = 0;
	return (0);
}

int			ft_key_press2(int key, t_app *app)
{
	if (key == 49 && app->jump == 0 && app->crouch == 0
			&& (app->move.v <= 0 || app->fly == 1))
	{
		app->jump = 1;
		app->jumping = 1;
	}
	else if (key == 3)
		app->fly = app->fly == 0 ? 1 : 0;
	else if (key == 8 && app->jump == 0)
		app->crouch = 1;
	else if (key == 69 && app->size < 2)
		app->size++;
	else if (key == 78 && app->size > 0 && app->move.v < app->size)
		app->size--;
	else if (key == 53)
		exit(0);
	return (0);
}

int			ft_key_press(int key, t_app *app)
{
	app->startscreen = 0;
	ft_motion(key, app, 1);
	if (key == 12)
	{
		app->weapon.fire_count = 0;
		app->weapon.is_fired = 1;
	}
	else if (key == 12)
		app->weapon.is_fired = 1;
	else if (key == 7)
		app->c = (app->c == 1) ? 0 : 1;
	else if (key == 18)
		app->is_weapon = 1;
	else if (key == 19)
		app->is_weapon = 0;
	else if (key == 257 && app->crouch == 0)
		app->speed = 1;
	ft_key_press2(key, app);
	return (0);
}
