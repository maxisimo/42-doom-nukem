/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:07:26 by lchappon          #+#    #+#             */
/*   Updated: 2019/01/16 18:05:30 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
	else if (key == 18)
		app->is_weapon = app->is_weapon == 0 ? 1 : 0;
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
	if (key == 49 && app->jump == 0 && app->crouch == 0 &&
		(app->fly == 1 || (app->map[(int)app->pos.x][(int)app->pos.y] < 12 &&
			app->move.v <= 0) || (app->map[(int)app->pos.x][(int)app->pos.y]
				>= 12 && app->move.v <= 2.4)))
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
	{
		system("/usr/bin/killall afplay 2&>/dev/null >/dev/null");
		exit(0);
	}
	return (0);
}

int			ft_key_press(int key, t_app *app)
{
	app->startscreen = (app->startscreen == 1) ? 2 : 0;
	ft_motion(key, app, 1);
	if (key == 12)
	{
		app->weapon.fire_count = 0;
		app->weapon.is_fired = 1;
	}
	else if (key == 7)
		app->c = (app->c == 1) ? 0 : 1;
	else if (key == 257 && app->crouch == 0)
		app->speed = 1;
	else if (key == 14)
		ft_doors(app);
	else if (key == 35)
		app->poster = app->poster == 0 ? 1 : 0;
	ft_key_press2(key, app);
	return (0);
}
