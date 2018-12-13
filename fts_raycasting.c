/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:20:06 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/13 12:35:21 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	dda_init(t_app *a)
{
	a->deltadistx = fabs(1 / a->ray.dir.x);
	a->deltadisty = fabs(1 / a->ray.dir.y);
	if (a->ray.dir.x < 0)
	{
		a->stepx = -1;
		a->sidedistx = (a->ray.pos.x - a->mapx) * a->deltadistx;
	}
	else
	{
		a->stepx = 1;
		a->sidedistx = (a->mapx + 1. - a->ray.pos.x) * a->deltadistx;
	}
	if (a->ray.dir.y < 0)
	{
		a->stepy = -1;
		a->sidedisty = (a->ray.pos.y - a->mapy) * a->deltadisty;
	}
	else
	{
		a->stepy = 1;
		a->sidedisty = (a->mapy + 1. - a->ray.pos.y) * a->deltadisty;
	}
}

static void	dda(t_app *a)
{
	a->hit = 0;
	while (a->hit == 0)
	{
		if (a->sidedistx < a->sidedisty)
		{
			a->sidedistx += a->deltadistx;
			a->mapx += a->stepx;
			a->side = 0;
		}
		else
		{
			a->sidedisty += a->deltadisty;
			a->mapy += a->stepy;
			a->side = 1;
		}
		if (a->map[a->mapy][a->mapx] > 0 && a->map[a->mapy][a->mapx] != 9)
			a->hit = 1;
	}
}

static void	raycasting_init(t_app *a, int x)
{
	a->cam.x = 2 * x / (double)WIN_W - 1;
	a->ray.pos.x = a->pos.y;
	a->ray.pos.y = a->pos.x;
	a->ray.dir.x = a->cam.dir.x + a->cam.plane.x * a->cam.x;
	a->ray.dir.y = a->cam.dir.y + a->cam.plane.y * a->cam.x;
	a->mapx = (int)a->ray.pos.x;
	a->mapy = (int)a->ray.pos.y;
	dda_init(a);
	dda(a);
	if (a->side == 0)
		a->dist_wall = (a->mapx - a->ray.pos.x + (1 - a->stepx) / 2) /
			a->ray.dir.x;
	else
		a->dist_wall = (a->mapy - a->ray.pos.y + (1 - a->stepy) / 2) /
			a->ray.dir.y;
}

void		ft_pthread(t_app *a)
{
	t_app		tab[4];
	pthread_t	t[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		tab[i] = *a;
		tab[i].main_a = a;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		tab[i].current_thread = i;
		pthread_create(&t[i], NULL, raycasting, &tab[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(t[i], NULL);
		i++;
	}
}

void		*raycasting(void *tab)
{
	t_app	a;

	a = *(t_app *)tab;
	a.p.x = (WIN_W / 4) * a.current_thread;
	a.p.xx = (WIN_W / 4) * (a.current_thread + 1);
	while (a.p.x < a.p.xx)
	{
		raycasting_init(&a, a.p.x);
		a.lineheight = (int)(WIN_H / a.dist_wall);
		a.start = -a.lineheight / 2 + WIN_H / 2;
		a.end = a.lineheight / 2 + WIN_H / 2;
		if (a.start < 0)
			a.start = 0;
		if (a.end > WIN_H)
			a.end = WIN_H;
		a.clr_intensity = (a.dist_wall < 0.35) ? 1 : 0.35 / a.dist_wall;
		a.zbuffer[a.p.x] = a.dist_wall;
		draw_wall(a.p.x, a.start, a.end, &a);
		a.main_a->zbuffer[a.p.x] = a.dist_wall;
		a.p.x++;
	}
	return (NULL);
}
