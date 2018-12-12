/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 11:15:41 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/12 06:00:39 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int			ft_key_press(int key, t_app *a)
{
	a->startscreen = 0;
	if (key == 13)
		a->move.up = 1;
	else if (key == 1)
		a->move.down = 1;
	else if (key == 2)
		a->move.right = 1;
	else if (key == 0)
		a->move.left = 1;
	else if (key == 123)
		a->rot.left = 1;
	else if (key == 124)
		a->rot.right = 1;
	else if (key == 126)
	{
		a->weapon.fire_count = 0;
		a->weapon.is_fired = 1;
	}
	ft_key_press2(key, a);
	return (0);
}

int			ft_key_press2(int key, t_app *a)
{
	if (key == 126)
		a->weapon.is_fired = 1;
	else if (key == 8)
		a->c = (a->c == 1) ? 0 : 1;
	else if (key == 18)
		a->is_weapon = 1;
	else if (key == 19)
		a->is_weapon = 0;
	else if (key == 257)
		a->speed = 1;
	else if (key == 53)
		exit(0);
	return (0);
}

int			ft_key_release(int key, t_app *a)
{
	if (key == 13)
		a->move.up = 0;
	else if (key == 1)
		a->move.down = 0;
	else if (key == 2)
		a->move.right = 0;
	else if (key == 0)
		a->move.left = 0;
	else if (key == 123)
		a->rot.left = 0;
	else if (key == 124)
		a->rot.right = 0;
	else if (key == 126)
		a->weapon.is_fired = 0;
	else if (key == 257)
		a->speed = 0;
	return (0);
}
