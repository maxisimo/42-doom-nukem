/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:44:13 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/08 13:44:35 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_poster(t_app *a)
{
	if (a->texx >= 12 && a->texx <= 52 && a->texy >= 8 && a->texy <= 56 &&
			a->map[a->mapy][a->mapx] < WINDOW && a->texy >= 0 &&
			((a->side == 0 && a->ray.dir.x < 0 &&
			a->map[a->mapy][a->mapx + 1] >= 0) ||
			(a->side == 0 && a->ray.dir.x > 0 &&
			a->map[a->mapy][a->mapx - 1] >= 0) ||
			(a->side == 1 && a->ray.dir.y < 0 &&
			a->map[a->mapy + 1][a->mapx] >= 0) ||
			(a->side == 1 && a->ray.dir.y > 0 &&
			a->map[a->mapy - 1][a->mapx] >= 0)))
		a->texnum = POSTER;
}
