/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 21:35:57 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/15 19:08:22 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_doors(t_app *a)
{
	if (fabs(a->cam.dir.x) > fabs(a->cam.dir.y))
	{
		if (a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == HDOOR &&
				a->move.v <= 1)
			a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] = HDOOR_O;
		else if (a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] ==
				HDOOR_O && a->map[(int)a->pos.x][(int)a->pos.y] != HDOOR_O &&
				a->move.v <= 1)
			a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] = HDOOR;
	}
	else if (fabs(a->cam.dir.x) < fabs(a->cam.dir.y))
	{
		if (a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == VDOOR &&
				a->move.v <= 1)
			a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] = VDOOR_O;
		else if (a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] ==
				VDOOR_O && a->map[(int)a->pos.x][(int)a->pos.y] != VDOOR_O &&
				a->move.v <= 1)
			a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] = VDOOR;
	}
	if (((a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == 13 &&
			fabs(a->cam.dir.x) > fabs(a->cam.dir.y)) ||
			(a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == 13 &&
			fabs(a->cam.dir.x) < fabs(a->cam.dir.y))) && a->move.v <= 1)
		a->screen_win = 1;
}

void	ft_door_side_entry(t_app *a)
{
	if (a->map[a->mapy][a->mapx] < WINDOW &&
			a->side == 0 && a->ray.dir.x < 0 &&
			a->map[a->mapy][a->mapx + 1] == VDOOR_O)
		a->texnum = DOOR2;
	else if (a->map[a->mapy][a->mapx] < WINDOW &&
			a->side == 0 && a->ray.dir.x > 0 &&
			a->map[a->mapy][a->mapx - 1] == VDOOR_O &&
			(a->map[a->mapy][a->mapx - 2] <= 0 ||
			a->map[a->mapy][a->mapx - 2] >= WINDOW))
		a->texnum = DOOR2;
	if (a->map[a->mapy][a->mapx] < WINDOW &&
			a->side == 1 && a->ray.dir.y < 0 &&
			a->map[a->mapy + 1][a->mapx] == HDOOR_O)
		a->texnum = DOOR2;
	else if (a->map[a->mapy][a->mapx] < WINDOW &&
			a->side == 1 && a->ray.dir.y > 0 &&
			a->map[a->mapy - 1][a->mapx] == HDOOR_O &&
			(a->map[a->mapy - 2][a->mapx] <= 0 ||
			a->map[a->mapy - 2][a->mapx] >= WINDOW))
		a->texnum = DOOR2;
}

void	ft_door_side(t_app *a)
{
	if (a->map[a->mapy][a->mapx] == VDOOR && a->side == 0)
		a->texnum = DOOR2;
	if (a->map[a->mapy][a->mapx] == HDOOR && a->side == 1)
		a->texnum = DOOR2;
	ft_door_side_entry(a);
}
