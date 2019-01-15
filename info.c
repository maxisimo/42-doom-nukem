/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:34:23 by lchappon          #+#    #+#             */
/*   Updated: 2019/01/15 19:06:38 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_info2(t_app *a)
{
	char	*txt;
	char	*stat;

	stat = ft_itoa(a->life);
	txt = ft_strjoin(stat, " HEALTH POINTS");
	mlx_string_put(a->mlx, a->win, 10, WIN_H - 30, 0xFFFFFF, txt);
	free(stat);
	free(txt);
	stat = ft_itoa(a->ammo);
	txt = ft_strjoin(stat, " AMMUNITIONS");
	mlx_string_put(a->mlx, a->win, 10, WIN_H - 50, 0xFFFFFF, txt);
	free(stat);
	free(txt);
	stat = ft_itoa(a->enemies_count2);
	txt = ft_strjoin(stat, " ENEMIES");
	mlx_string_put(a->mlx, a->win, 10, WIN_H - 70, 0xFFFFFF, txt);
	free(stat);
	free(txt);
}

void	ft_info(t_app *a)
{
	if (((a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == HDOOR &&
			fabs(a->cam.dir.x) > fabs(a->cam.dir.y)) ||
			(a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == VDOOR &&
			fabs(a->cam.dir.x) < fabs(a->cam.dir.y))) &&
			a->move.v <= 1)
		mlx_string_put(a->mlx, a->win, WIN_WD, WIN_HD, 0xFFFFFF, OPEN);
	if (((a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == HDOOR_O &&
			fabs(a->cam.dir.x) > fabs(a->cam.dir.y) &&
			a->map[(int)a->pos.x][(int)a->pos.y] != HDOOR_O) ||
			(a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == VDOOR_O &&
			fabs(a->cam.dir.x) < fabs(a->cam.dir.y) &&
			a->map[(int)a->pos.x][(int)a->pos.y] != VDOOR_O)) &&
			a->move.v <= 1)
		mlx_string_put(a->mlx, a->win, WIN_WD, WIN_HD, 0xFFFFFF, CLOSE);
	if (((a->map[(int)a->pos.x][(int)(a->pos.y + a->cam.dir.x)] == 13 &&
			fabs(a->cam.dir.x) > fabs(a->cam.dir.y)) ||
			(a->map[(int)(a->pos.x + a->cam.dir.y)][(int)a->pos.y] == 13 &&
			fabs(a->cam.dir.x) < fabs(a->cam.dir.y))) &&
			a->move.v <= 1)
		mlx_string_put(a->mlx, a->win, WIN_WD - 40, WIN_HD, 0xFFFFFF, END);
	ft_info2(a);
}
