/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 11:31:02 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/12 06:02:42 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	ft_rotate(t_app *a)
{
	a->ms = (a->speed == 1) ? 0.1 : 0.07;
	if (a->rot.right == 1)
	{
		a->old_dir_x = a->dir_x;
		a->dir_x = a->dir_x * cos(-0.05) - a->dir_y * sin(-0.05);
		a->dir_y = a->old_dir_x * sin(-0.05) + a->dir_y * cos(-0.05);
		a->oldplane_x = a->plane_x;
		a->plane_x = a->plane_x * cos(-0.05) - a->plane_y * sin(-0.05);
		a->plane_y = a->oldplane_x * sin(-0.05) + a->plane_y * cos(-0.05);
	}
	if (a->rot.left == 1)
	{
		a->old_dir_x = a->dir_x;
		a->dir_x = a->dir_x * cos(0.05) - a->dir_y * sin(0.05);
		a->dir_y = a->old_dir_x * sin(0.05) + a->dir_y * cos(0.05);
		a->oldplane_x = a->plane_x;
		a->plane_x = a->plane_x * cos(0.05) - a->plane_y * sin(0.05);
		a->plane_y = a->oldplane_x * sin(0.05) + a->plane_y * cos(0.05);
	}
}

static void	ft_move2(t_app *a)
{
	if (a->move.left == 1)
	{
		if ((a->map[(int)(a->pos.x + a->dir_x * a->ms)][(int)(a->pos.y)] == 0) ||
				a->map[(int)(a->pos.x + a->dir_x * a->ms)][(int)(a->pos.y)] == 9)
			a->pos.x += a->dir_x * a->ms;
		if ((a->map[(int)(a->pos.x)][(int)(a->pos.y - a->dir_y * a->ms)] == 0) ||
				a->map[(int)(a->pos.x)][(int)(a->pos.y - a->dir_y * a->ms)] == 9)
			a->pos.y -= a->dir_y * a->ms;
	}
	if (a->move.right == 1)
	{
		if ((a->map[(int)(a->pos.x - a->dir_x * a->ms)][(int)(a->pos.y)] == 0) ||
				a->map[(int)(a->pos.x - a->dir_x * a->ms)][(int)(a->pos.y)] == 9)
			a->pos.x -= a->dir_x * a->ms;
		if ((a->map[(int)(a->pos.x)][(int)(a->pos.y + a->dir_y * a->ms)] == 0) ||
				a->map[(int)(a->pos.x)][(int)(a->pos.y + a->dir_y * a->ms)] == 9)
			a->pos.y += a->dir_y * a->ms;
	}
}

int			ft_move(t_app *a)
{
	if (a->move.up == 1)
	{
		if ((a->map[(int)(a->pos.x + a->dir_y * a->ms)][(int)(a->pos.y)] == 0) ||
				a->map[(int)(a->pos.x + a->dir_y * a->ms)][(int)(a->pos.y)] == 9)
			a->pos.x += a->dir_y * a->ms;
		if ((a->map[(int)(a->pos.x)][(int)(a->pos.y + a->dir_x * a->ms)] == 0) ||
				a->map[(int)(a->pos.x)][(int)(a->pos.y + a->dir_x * a->ms)] == 9)
			a->pos.y += a->dir_x * a->ms;
	}
	if (a->move.down == 1)
	{
		if ((a->map[(int)(a->pos.x - a->dir_y * a->ms)][(int)(a->pos.y)] == 0) ||
				a->map[(int)(a->pos.x - a->dir_y * a->ms)][(int)(a->pos.y)] == 9)
			a->pos.x -= a->dir_y * a->ms;
		if ((a->map[(int)(a->pos.x)][(int)(a->pos.y - a->dir_x * a->ms)] == 0) ||
				a->map[(int)(a->pos.x)][(int)(a->pos.y - a->dir_x * a->ms)] == 9)
			a->pos.y -= a->dir_x * a->ms;
	}
	ft_move2(a);
	ft_rotate(a);
	return (0);
}
