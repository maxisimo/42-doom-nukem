/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:12:53 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/10 20:32:10 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		enemies_ai(t_app *a, t_enemy *e)
{
	if (a->pos.x + 0.5 > e->pos.x && a->pos.x - e->pos.x < 6 &&
			a->map[(int)(e->pos.x + 0.25)][(int)(e->pos.y)] <= 0)
		e->pos.x += 0.02;
	if (a->pos.x - 0.5 < e->pos.x && a->pos.x - e->pos.x > -6 &&
			a->map[(int)(e->pos.x - 0.25)][(int)(e->pos.y)] <= 0)
		e->pos.x -= 0.02;
	if (a->pos.y + 0.5 > e->pos.y && a->pos.y - e->pos.y < 6 &&
			a->map[(int)(e->pos.x)][(int)(e->pos.y + 0.25)] <= 0)
		e->pos.y += 0.02;
	if (a->pos.y - 0.5 < e->pos.y && a->pos.y - e->pos.y > -6 &&
			a->map[(int)(e->pos.x)][(int)(e->pos.y - 0.25)] <= 0)
		e->pos.y -= 0.02;
	if (e->sprite.dist <= 1 && a->move.v <= 1)
		a->life -= 1;
}

void		enemies_sort(t_app *a)
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

void		enemies_pick(t_app *a, t_enemy *e)
{
	if (e->type == 1 && e->sprite.dist <= 0.5 && a->move.v <= 1)
	{
		if (a->life < 200 || a->ammo < 300)
			e->life = 0;
		if (a->life < 200)
			a->life += 20;
		if (a->life > 200)
			a->life = 200;
		if (a->ammo < 300)
			a->ammo += 30;
		if (a->ammo > 300)
			a->ammo = 300;
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
			enemies_pick(a, &a->enemies[i]);
			if (a->enemies[i].type == 0)
				enemies_ai(a, &a->enemies[i]);
			sprites_draw(a, &a->enemies[i]);
		}
		i++;
	}
}
