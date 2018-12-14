/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 11:31:02 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/14 14:10:22 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	ft_rotate(t_app *a)
{
	if (a->rot.right == 1)
		a->rs = -0.05;
	if (a->rot.left == 1)
		a->rs = 0.05;
	a->old_dir_x = a->cam.dir.x;
	a->cam.dir.x = a->cam.dir.x * cos(a->rs) - a->cam.dir.y * sin(a->rs);
	a->cam.dir.y = a->old_dir_x * sin(a->rs) + a->cam.dir.y * cos(a->rs);
	a->oldplane_x = a->cam.plane.x;
	a->cam.plane.x = a->cam.plane.x * cos(a->rs) - a->cam.plane.y * sin(a->rs);
	a->cam.plane.y = a->oldplane_x * sin(a->rs) + a->cam.plane.y * cos(a->rs);
	a->rs = 0;
	if (a->rot.up == 1 && a->rot.v < WIN_H / 2)
		a->rot.v += 20;
	if (a->rot.down == 1 && a->rot.v > -WIN_H / 2)
		a->rot.v -= 20;
}

static void	ft_move2(t_app *a)
{
	if (a->move.left == 1)
	{
		if ((a->map[(int)(a->pos.x + a->cam.dir.x * a->ms)][(int)(a->pos.y)] == 0) ||
				a->map[(int)(a->pos.x + a->cam.dir.x * a->ms)][(int)(a->pos.y)] == 9)
			a->pos.x += a->cam.dir.x * a->ms;
		if ((a->map[(int)(a->pos.x)][(int)(a->pos.y - a->cam.dir.y * a->ms)] == 0) ||
				a->map[(int)(a->pos.x)][(int)(a->pos.y - a->cam.dir.y * a->ms)] == 9)
			a->pos.y -= a->cam.dir.y * a->ms;
	}
	if (a->move.right == 1)
	{
		if ((a->map[(int)(a->pos.x - a->cam.dir.x * a->ms)][(int)(a->pos.y)] == 0) ||
				a->map[(int)(a->pos.x - a->cam.dir.x * a->ms)][(int)(a->pos.y)] == 9)
			a->pos.x -= a->cam.dir.x * a->ms;
		if ((a->map[(int)(a->pos.x)][(int)(a->pos.y + a->cam.dir.y * a->ms)] == 0) ||
				a->map[(int)(a->pos.x)][(int)(a->pos.y + a->cam.dir.y * a->ms)] == 9)
			a->pos.y += a->cam.dir.y * a->ms;
	}
}

int			ft_move(t_app *a)
{
	a->ms = (a->speed == 1) ? 0.12 : 0.09;
	if (a->move.up == 1)
	{
		if ((a->map[(int)(a->pos.x + a->cam.dir.y * a->ms)][(int)(a->pos.y)] == 0) ||
				a->map[(int)(a->pos.x + a->cam.dir.y * a->ms)][(int)(a->pos.y)] == 9)
			a->pos.x += a->cam.dir.y * a->ms;
		if ((a->map[(int)(a->pos.x)][(int)(a->pos.y + a->cam.dir.x * a->ms)] == 0) ||
				a->map[(int)(a->pos.x)][(int)(a->pos.y + a->cam.dir.x * a->ms)] == 9)
			a->pos.y += a->cam.dir.x * a->ms;
	}
	if (a->move.down == 1)
	{
		if ((a->map[(int)(a->pos.x - a->cam.dir.y * a->ms)][(int)(a->pos.y)] == 0) ||
				a->map[(int)(a->pos.x - a->cam.dir.y * a->ms)][(int)(a->pos.y)] == 9)
			a->pos.x -= a->cam.dir.y * a->ms;
		if ((a->map[(int)(a->pos.x)][(int)(a->pos.y - a->cam.dir.x * a->ms)] == 0) ||
				a->map[(int)(a->pos.x)][(int)(a->pos.y - a->cam.dir.x * a->ms)] == 9)
			a->pos.y -= a->cam.dir.x * a->ms;
	}
	ft_move2(a);
	ft_rotate(a);
	return (0);
}
