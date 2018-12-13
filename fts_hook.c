/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 11:15:41 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/13 16:57:05 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

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
	else if (key == 126)
	{
		app->weapon.fire_count = 0;
		app->weapon.is_fired = 1;
	}
	ft_key_press2(key, app);
	return (0);
}

int			ft_key_press2(int key, t_app *app)
{
	if (key == 126)
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
	else if (key == 126)
		app->weapon.is_fired = 0;
	else if (key == 257)
		app->speed = 0;
	return (0);
}
