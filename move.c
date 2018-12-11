/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:40:55 by lchappon          #+#    #+#             */
/*   Updated: 2018/12/11 17:06:24 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	ft_rotate(t_e *e)
{
	double	tmp;

	if (e->rot.right == 1)
		e->rot.speed = 0.02;
	if (e->rot.left == 1)
		e->rot.speed = -0.02;
	tmp = e->cam.dir.x;
	e->cam.dir.x = e->cam.dir.x * cos(e->rot.speed) -
		e->cam.dir.y * sin(e->rot.speed);
	e->cam.dir.y = tmp * sin(e->rot.speed) +
		e->cam.dir.y * cos(e->rot.speed);
	tmp = e->cam.plane.x;
	e->cam.plane.x = e->cam.plane.x * cos(e->rot.speed) -
		e->cam.plane.y * sin(e->rot.speed);
	e->cam.plane.y = tmp * sin(e->rot.speed) +
		e->cam.plane.y * cos(e->rot.speed);
	e->rot.speed = 0;
	if (e->rot.up == 1 && e->rot.v < WIN_H / 2)
		e->rot.v += 20;
	if (e->rot.down == 1 && e->rot.v > -WIN_H / 2)
		e->rot.v -= 20;
}

void	ft_jump_and_crouch(t_e *e)
{
	if (e->move.fly == 0)
	{
		if (e->move.up2 == 1 && e->move.v < 0.8)
			e->move.v += 0.075;
		if (e->move.up == 0 || e->move.v >= 0.8)
			e->move.up2 = 0;
		if (e->move.up2 == 0 && e->move.v > 0)
			e->move.v -= 0.075;
	}
	else
	{
		if (e->move.up == 1 && e->move.v < 0.9 /*+ e->wall.size * 2*/)
			e->move.v += 0.025;
		if (e->move.up == 0 && e->move.v > 0)
			e->move.v -= 0.025;
	}
	if (e->move.down == 1 && e->move.v > -0.5)
		e->move.v -= 0.1;
	if (e->move.down == 0 && e->move.v < 0)
	{
		e->move.v += 0.1;
		e->move.v = e->move.v > 0 ? 0 : e->move.v;
	}
}

void	ft_strafe(t_e *e)
{
	if (e->move.right == 1)
	{
		if (e->map[(int)e->cam.pos.y]
				[(int)(e->cam.pos.x + e->cam.plane.x * e->move.speed)] <= 0)
			e->cam.pos.x += e->cam.plane.x * e->move.speed;
		if (e->map[(int)(e->cam.pos.y + e->cam.plane.y * e->move.speed)]
				[(int)e->cam.pos.x] <= 0)
			e->cam.pos.y += e->cam.plane.y * e->move.speed;
	}
	if (e->move.left == 1)
	{
		if (e->map[(int)e->cam.pos.y]
				[(int)(e->cam.pos.x - e->cam.plane.x * e->move.speed)] <= 0)
			e->cam.pos.x -= e->cam.plane.x * e->move.speed;
		if (e->map[(int)(e->cam.pos.y - e->cam.plane.y * e->move.speed)]
				[(int)e->cam.pos.x] <= 0)
			e->cam.pos.y -= e->cam.plane.y * e->move.speed;
	}
}

void	ft_move(t_e *e)
{
	if (e->move.forward == 1)
	{
		if (e->map[(int)e->cam.pos.y]
				[(int)(e->cam.pos.x + e->cam.dir.x * e->move.speed)] <= 0)
			e->cam.pos.x += e->cam.dir.x * e->move.speed;
		if (e->map[(int)(e->cam.pos.y + e->cam.dir.y * e->move.speed)]
				[(int)e->cam.pos.x] <= 0)
			e->cam.pos.y += e->cam.dir.y * e->move.speed;
	}
	if (e->move.backward == 1)
	{
		if (e->map[(int)e->cam.pos.y]
				[(int)(e->cam.pos.x - e->cam.dir.x * e->move.speed)] <= 0)
			e->cam.pos.x -= e->cam.dir.x * e->move.speed;
		if (e->map[(int)(e->cam.pos.y - e->cam.dir.y * e->move.speed)]
				[(int)e->cam.pos.x] <= 0)
			e->cam.pos.y -= e->cam.dir.y * e->move.speed;
	}
	ft_strafe(e);
	ft_jump_and_crouch(e);
	ft_rotate(e);
}
