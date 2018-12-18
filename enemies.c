/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:12:53 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/18 15:40:42 by lchappon         ###   ########.fr       */
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
	printf("enemies = %d\n", a->enemies_count);
}

void		enemies_ai(t_app *a, t_coord_d *pos)
{
	if (a->pos.x > pos->x && a->pos.x - pos->x < 5 &&
			a->map[(int)(pos->x + 0.25)][(int)(pos->y)] == 0)
		pos->x += 0.02;
	if (a->pos.x < pos->x && a->pos.x - pos->x > -5 &&
			a->map[(int)(pos->x - 0.25)][(int)(pos->y)] == 0)
		pos->x -= 0.02;
	if (a->pos.y > pos->y && a->pos.y - pos->y < 5 &&
			a->map[(int)(pos->x)][(int)(pos->y + 0.25)] == 0)
		pos->y += 0.02;
	if (a->pos.y < pos->y && a->pos.y - pos->y > -5 &&
			a->map[(int)(pos->x)][(int)(pos->y - 0.25)] == 0)
		pos->y -= 0.02;
}

void		enemies_draw(t_app *a)
{
	int i;

	i = 0;
	// SORT ENEMIES HERE
	sort_sprites(a);
	while (i < a->enemies_count)
	{
		sprites_draw(a, a->enemies[i].sprite, &a->enemies[i].pos);
		enemies_ai(a, &a->enemies[i].pos);
		i++;
	}
}
