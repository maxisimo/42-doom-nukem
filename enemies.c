/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:12:53 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/23 18:01:36 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	enemies_count(t_app *a)
{
	t_coord p;

	p.y = 0;
	a->enemies_count = 0;
	while (p.y < a->map_size.y)
	{
		p.x = 0;
		while (p.x < a->map_size.x)
		{
			if (a->map[p.x][p.y] == 10)
			{
				a->enemies_count++;
			}
			p.x++;
		}
		p.y++;
	}
}

static void	enemies_alloc(t_app *a)
{
	a->enemies = malloc(sizeof(t_enemy) * a->enemies_count);
	if (!(a->enemies))
		exit(-1);
}

static void	enemies_get_pos(t_app *a)
{
	t_coord	p;
	int		i;

	p.y = 0;
	i = 0;
	while (p.y < a->map_size.y)
	{
		p.x = 0;
		while (p.x < a->map_size.x)
		{
			if (a->map[p.x][p.y] == 10)
			{
				a->enemies[i].pos.y = (double)p.y + 0.5;
				a->enemies[i].pos.x = (double)p.x + 0.5;
				a->enemies[i].sprite.img = &a->sprites[2];
				a->enemies[i].life = 100;
				a->map[p.x][p.y] = 0;
				printf("-> %f %f\n", a->enemies[i].pos.x, a->enemies[i].pos.y);
				i++;
			}
			p.x++;
		}
		p.y++;
	}
}

void		enemies_init(t_app *a)
{
	enemies_count(a);
	enemies_alloc(a);
	enemies_get_pos(a);
}

void		enemies_ai(t_app *a, t_enemy *e)
{
	if (a->pos.x > e->pos.x && a->pos.x - e->pos.x < 6 &&
			a->map[(int)(e->pos.x + 0.25)][(int)(e->pos.y)] == 0)
		e->pos.x += 0.02;
	if (a->pos.x < e->pos.x && a->pos.x - e->pos.x > -6 &&
			a->map[(int)(e->pos.x - 0.25)][(int)(e->pos.y)] == 0)
		e->pos.x -= 0.02;
	if (a->pos.y > e->pos.y && a->pos.y - e->pos.y < 6 &&
			a->map[(int)(e->pos.x)][(int)(e->pos.y + 0.25)] == 0)
		e->pos.y += 0.02;
	if (a->pos.y < e->pos.y && a->pos.y - e->pos.y > -6 &&
			a->map[(int)(e->pos.x)][(int)(e->pos.y - 0.25)] == 0)
		e->pos.y -= 0.02;
	if (e->sprite.dist < 0.5)
		a->life -= 0.5;
}

void	enemies_sort(t_app *a)
{
	int		i;
	t_enemy	tmp;

	i = 0;
	while (i < a->enemies_count)
	{
		if (a->enemies[i].sprite.dist < a->enemies[i + 1].sprite.dist)
		{
			tmp = a->enemies[i];
			a->enemies[i] = a->enemies[i + 1];
			a->enemies[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void		enemies_draw(t_app *a)
{
	int i;

	i = 0;
	while (i < a->enemies_count)
	{
		a->enemies[i].sprite.spr_x = a->enemies[i].pos.x - a->pos.x;
		a->enemies[i].sprite.spr_y = a->enemies[i].pos.y - a->pos.y;
		a->enemies[i].sprite.dist =
			a->enemies[i].sprite.spr_x * a->enemies[i].sprite.spr_x +
			a->enemies[i].sprite.spr_y * a->enemies[i].sprite.spr_y;
		i++;
	}
	enemies_sort(a);
	i = 0;
	while (i < a->enemies_count)
	{
		if (a->enemies[i].life > 0)
		{
			sprites_draw(a, &a->enemies[i]);
			enemies_ai(a, &a->enemies[i]);
		}
		i++;
	}
}
