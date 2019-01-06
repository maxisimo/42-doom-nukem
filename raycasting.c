/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:08:44 by lchappon          #+#    #+#             */
/*   Updated: 2019/01/06 18:11:28 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	dda_init(t_app *app)
{
	if (app->ray.dir.x < 0)
	{
		app->ray.step.x = -1;
		app->wall.side_dist.x = (app->ray.pos.x - app->mapx) *
			app->wall.deltadist.x;
	}
	else
	{
		app->ray.step.x = 1;
		app->wall.side_dist.x = (app->mapx + 1. - app->ray.pos.x) *
			app->wall.deltadist.x;
	}
	if (app->ray.dir.y < 0)
	{
		app->ray.step.y = -1;
		app->wall.side_dist.y = (app->ray.pos.y - app->mapy) *
			app->wall.deltadist.y;
	}
	else
	{
		app->ray.step.y = 1;
		app->wall.side_dist.y = (app->mapy + 1. - app->ray.pos.y) *
			app->wall.deltadist.y;
	}
}

static void	dda(t_app *app)
{
	while (app->map[app->mapy][app->mapx] <= 0 ||
			(app->map[app->mapy][app->mapx] == WINDOW && app->p.x % 2 != 0) ||
			app->map[app->mapy][app->mapx] >= 12)
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
	}
}

static void	raycasting_init(t_app *app)
{
	app->camx = 2 * app->p.x / (double)WIN_W - 1;
	app->ray.pos.x = app->pos.y;
	app->ray.pos.y = app->pos.x;
	app->ray.dir.x = app->cam.dir.x + app->cam.plane.x * app->camx;
	app->ray.dir.y = app->cam.dir.y + app->cam.plane.y * app->camx;
	app->mapx = (int)app->ray.pos.x;
	app->mapy = (int)app->ray.pos.y;
	app->wall.deltadist.x = fabs(1 / app->ray.dir.x);
	app->wall.deltadist.y = fabs(1 / app->ray.dir.y);
	dda_init(app);
	dda(app);
	if (app->side == 0)
		app->wall.dist = (app->mapx - app->ray.pos.x +
				(1 - app->ray.step.x) / 2) / app->ray.dir.x;
	else
		app->wall.dist = (app->mapy - app->ray.pos.y +
				(1 - app->ray.step.y) / 2) / app->ray.dir.y;
	app->lineheight = (int)(WIN_H / app->wall.dist);
	app->start = -app->lineheight / 2;
	app->start -= app->start * app->move.v;
	app->start += WIN_H / 2 + app->rot.v;
	app->start -= app->lineheight * app->size;
	app->end = app->lineheight / 2;
	app->end += app->end * app->move.v;
	app->end += WIN_H / 2 + app->rot.v;
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
		raycasting_init(&a);
		if (a.start < 0)
			a.start = 0;
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
