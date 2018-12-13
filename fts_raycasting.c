/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:20:06 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/13 19:24:02 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	dda_init(t_app *app)
{
	app->wall.deltadist.x = fabs(1 / app->ray.dir.x);
	app->wall.deltadist.y = fabs(1 / app->ray.dir.y);
	if (app->ray.dir.x < 0)
	{
		app->ray.step.x = -1;
		app->wall.side_dist.x = (app->ray.pos.x - app->mapx) * app->wall.deltadist.x;
	}
	else
	{
		app->ray.step.x = 1;
		app->wall.side_dist.x = (app->mapx + 1. - app->ray.pos.x) * app->wall.deltadist.x;
	}
	if (app->ray.dir.y < 0)
	{
		app->ray.step.y = -1;
		app->wall.side_dist.y = (app->ray.pos.y - app->mapy) * app->wall.deltadist.y;
	}
	else
	{
		app->ray.step.y = 1;
		app->wall.side_dist.y = (app->mapy + 1. - app->ray.pos.y) * app->wall.deltadist.y;
	}
}

static void	dda(t_app *app)
{
	app->hit = 0;
	while (app->hit == 0)
	{
		if (app->wall.side_dist.x < app->wall.side_dist.y)
		{
			app->wall.side_dist.x += app->wall.deltadist.x;
			app->mapx += app->ray.step.x;
			app->side = 0;
		}
		else
		{
			app->wall.side_dist.y += app->wall.deltadist.y;
			app->mapy += app->ray.step.y;
			app->side = 1;
		}
		if (app->map[app->mapy][app->mapx] > 0 && app->map[app->mapy][app->mapx] != 9)
			app->hit = 1;
	}
}

static void	raycasting_init(t_app *app, int x)
{
	app->camx = 2 * x / (double)WIN_W - 1;
	app->ray.pos.x = app->pos.y;
	app->ray.pos.y = app->pos.x;
	app->ray.dir.x = app->cam.dir.x + app->cam.plane.x * app->camx;
	app->ray.dir.y = app->cam.dir.y + app->cam.plane.y * app->camx;
	app->mapx = (int)app->ray.pos.x;
	app->mapy = (int)app->ray.pos.y;
	dda_init(app);
	dda(app);
	if (app->side == 0)
		app->wall.dist = (app->mapx - app->ray.pos.x + (1 - app->ray.step.x) / 2) /
			app->ray.dir.x;
	else
		app->wall.dist = (app->mapy - app->ray.pos.y + (1 - app->ray.step.y) / 2) /
			app->ray.dir.y;
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
		a.lineheight = (int)(WIN_H / a.wall.dist);
		a.start = -a.lineheight / 2 + WIN_H / 2 + a.rot.v;
		a.end = a.lineheight / 2 + WIN_H / 2 + a.rot.v;
		if (a.start < 0)
			a.start = 0;
		if (a.start > WIN_H)
			a.start = WIN_H;
		if (a.end < 0)
			a.end = 0;
		if (a.end > WIN_H)
			a.end = WIN_H;
		a.wall.clr_intensity = (a.wall.dist < 0.35) ? 1 : 0.35 / a.wall.dist;
		a.zbuffer[a.p.x] = a.wall.dist;
		draw_wall(a.p.x, a.start, a.end, &a);
		a.main_a->zbuffer[a.p.x] = a.wall.dist;
		a.p.x++;
	}
	return (NULL);
}
