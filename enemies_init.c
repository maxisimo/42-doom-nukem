/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 19:26:34 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/16 12:45:08 by maxisimo         ###   ########.fr       */
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
			if (a->map[p.x][p.y] >= 10 && a->map[p.x][p.y] <= 13)
				a->enemies_count++;
			if (a->map[p.x][p.y] == 10)
				a->enemies_count2++;
			p.x++;
		}
		p.y++;
	}
}

static void	enemies_alloc(t_app *a)
{
	a->enemies = ft_memalloc(sizeof(t_enemy) * a->enemies_count);
	if (!(a->enemies))
		exit(-1);
}

static void	enemies_get_type(t_app *a, t_coord p, int i)
{
	a->enemies[i].pos.y = (double)p.y + 0.5;
	a->enemies[i].pos.x = (double)p.x + 0.5;
	a->enemies[i].life = 100;
	a->map[p.x][p.y] == 10 ? a->enemies[i].type = 0 : 0;
	a->map[p.x][p.y] == 11 ? a->enemies[i].type = 1 : 0;
	a->map[p.x][p.y] == 12 ? a->enemies[i].type = 2 : 0;
	a->map[p.x][p.y] == 13 ? a->enemies[i].type = 3 : 0;
	if (a->map[p.x][p.y] < 12)
		a->map[p.x][p.y] = 0;
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
			if (a->map[p.x][p.y] >= 10 && a->map[p.x][p.y] <= 13)
			{
				enemies_get_type(a, p, i);
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
