/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:08:17 by lchappon          #+#    #+#             */
/*   Updated: 2018/12/29 14:35:12 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		ft_doors(t_app *a)
{
	if (a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == HDOOR &&
			a->move.v <= 1)
		a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] = HDOOR_O;
	else if (a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == HDOOR_O &&
			a->map[(int)a->pos.x][(int)a->pos.y] != HDOOR_O &&
			a->move.v <= 1)
		a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] = HDOOR;
	if (a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == VDOOR &&
			a->move.v <= 1)
		a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] = VDOOR_O;
	else if (a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == VDOOR_O &&
			a->map[(int)a->pos.x][(int)a->pos.y] != VDOOR_O &&
			a->move.v <= 1)
		a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] = VDOOR;
}

void		ft_rotate(t_app *a)
{
	double	tmp;

	if (a->rot.right == 1)
		a->rot.s = -0.05;
	if (a->rot.left == 1)
		a->rot.s = 0.05;
	tmp = a->cam.dir.x;
	a->cam.dir.x = a->cam.dir.x * cos(a->rot.s) - a->cam.dir.y * sin(a->rot.s);
	a->cam.dir.y = tmp * sin(a->rot.s) + a->cam.dir.y * cos(a->rot.s);
	tmp = a->cam.plane.x;
	a->cam.plane.x = a->cam.plane.x * cos(a->rot.s) -
		a->cam.plane.y * sin(a->rot.s);
	a->cam.plane.y = tmp * sin(a->rot.s) +
		a->cam.plane.y * cos(a->rot.s);
	a->rot.s = 0;
	if (a->rot.up == 1 && a->rot.v < WIN_H / 2)
		a->rot.v += 20;
	if (a->rot.down == 1 && a->rot.v > -WIN_H / 2)
		a->rot.v -= 20;
}

static void	ft_move3(t_app *a)
{
	if (a->fly == 0)
	{
		if (a->jumping == 1 && a->move.v < 0.8)
			a->move.v += 0.1;
		if (a->jump == 0 || a->move.v >= 0.8)
			a->jumping = 0;
		if (a->jumping == 0 && a->move.v > 0)
			a->move.v -= 0.1;
	}
	else
	{
		if (a->jump == 1 && a->move.v < 0.9 + a->size * 2)
			a->move.v += 0.05;
		if (a->jump == 0 && a->move.v > 0)
			a->move.v -= 0.05;
	}
	if (a->crouch == 1 && a->move.v > -0.5)
		a->move.v -= 0.1;
	if (a->crouch == 0 && a->move.v < 0)
	{
		a->move.v += 0.1;
		a->move.v = a->move.v > 0 ? 0 : a->move.v;
	}
}

static void	ft_move2(t_app *a)
{
	if (a->move.left == 1)
	{
		if (a->map[(int)(a->pos.x + a->cam.dir.x * a->move.s)][(int)(a->pos.y)]
				<= 0)
			a->pos.x += a->cam.dir.x * a->move.s;
		if (a->map[(int)(a->pos.x)][(int)(a->pos.y - a->cam.dir.y * a->move.s)]
				<= 0)
			a->pos.y -= a->cam.dir.y * a->move.s;
	}
	if (a->move.right == 1)
	{
		if (a->map[(int)(a->pos.x - a->cam.dir.x * a->move.s)][(int)(a->pos.y)]
				<= 0)
			a->pos.x -= a->cam.dir.x * a->move.s;
		if (a->map[(int)(a->pos.x)][(int)(a->pos.y + a->cam.dir.y * a->move.s)]
				<= 0)
			a->pos.y += a->cam.dir.y * a->move.s;
	}
}

int			ft_move(t_app *a)
{
	a->move.s = (a->speed == 1) ? 0.12 : 0.09;
	a->move.s = (a->crouch == 1) ? 0.03 : a->move.s;
	if (a->move.up == 1)
	{
		if (a->map[(int)(a->pos.x + a->cam.dir.y * a->move.s)][(int)(a->pos.y)]
				<= 0)
			a->pos.x += a->cam.dir.y * a->move.s;
		if (a->map[(int)(a->pos.x)][(int)(a->pos.y + a->cam.dir.x * a->move.s)]
				<= 0)
			a->pos.y += a->cam.dir.x * a->move.s;
	}
	if (a->move.down == 1)
	{
		if (a->map[(int)(a->pos.x - a->cam.dir.y * a->move.s)][(int)(a->pos.y)]
				<= 0)
			a->pos.x -= a->cam.dir.y * a->move.s;
		if (a->map[(int)(a->pos.x)][(int)(a->pos.y - a->cam.dir.x * a->move.s)]
				<= 0)
			a->pos.y -= a->cam.dir.x * a->move.s;
	}
	ft_move2(a);
	ft_move3(a);
	return (0);
}
