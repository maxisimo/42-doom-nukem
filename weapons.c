/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 17:30:54 by thbernar          #+#    #+#             */
/*   Updated: 2018/12/13 18:17:30 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	weapons_fire(t_app *a)
{
	t_coord	tmp;

	tmp.x = WIN_W - a->weapon.img.width;
	tmp.y = WIN_H - a->weapon.img.height;
	if (a->weapon.fire_count % 2 == 0)
		ft_put_bmp_to_img(a, a->weapon.img, tmp.x, tmp.y);
	else
		ft_put_bmp_to_img(a, a->weapon.img, tmp.x - 10, tmp.y);
	a->weapon.fire_count++;
}

void		weapons_draw_weapon(t_app *a)
{
	t_coord	tmp;
	t_coord tmp2;

	if (a->is_weapon == 1)
	{
		tmp.x = WIN_W - a->weapon.img.width;
		tmp.y = WIN_H - a->weapon.img.height;
		tmp2.x = WIN_W / 2 - a->weapon.scope.width / 2;
		tmp2.y = WIN_H / 2 - a->weapon.scope.height / 2;
		if (a->weapon.is_fired)
			weapons_fire(a);
		else
			ft_put_bmp_to_img(a, a->weapon.img, tmp.x, tmp.y);
		ft_put_bmp_to_img(a, a->weapon.scope, tmp2.x, tmp2.y);
	}
}
