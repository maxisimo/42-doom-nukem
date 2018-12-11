/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:06:30 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/11 16:41:39 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int			expose_hook(t_e *e)
{
	if (e->startscreen == 0)
		ft_start_screen(e);
	else
		ft_move(e);
	return (0);
}

int			ft_key_press(int key, t_e *e)
{
    ++e->startscreen;
	e->startscreen = (e->startscreen > 0) ? 1 : e->startscreen;
	if (key == 13)
		e->move.up = 1;
	else if (key == 1)
		e->move.down = 1;
	else if (key == 2)
		e->move.right = 1;
	else if (key == 0)
		e->move.left = 1;
	else if (key == 123)
		e->rot.left = 1;
	else if (key == 124)
		e->rot.right = 1;
	else if (key == 126)
		e->rot.up = 1;
	else if (key == 125)
		e->rot.down = 1;
	ft_key_press2(key, e);
	return (0);
}

int			ft_key_press2(int key, t_e *e)
{
    if (key == 49 && e->move.up == 0 &&
			(e->move.v <= 0 || e->move.fly == 1) && e->move.down == 0)
	{
		e->move.up = 1;
		e->move.up2 = 1;
	}
	if (key == 8 && e->move.up == 0)
	{
		e->move.down = 1;
		e->move.speed = 0.025;
	}
	else if (key == 257)
		e->move.speed = 1;
	else if (key == 53)
		exit(0);
	return (0);
}

int			ft_key_release(int key, t_e *e)
{
	if (key == 13)
		e->move.up = 0;
	else if (key == 1)
		e->move.down = 0;
	else if (key == 2)
		e->move.right = 0;
	else if (key == 0)
		e->move.left = 0;
	else if (key == 123)
		e->rot.left = 0;
	else if (key == 124)
		e->rot.right = 0;
	else if (key == 126)
		e->rot.up = 0;
	else if (key == 125)
		e->rot.down = 0;
	else if (key == 257)
		e->move.speed = 0;
	return (0);
}