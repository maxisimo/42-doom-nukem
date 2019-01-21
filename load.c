/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:54:23 by thbernar          #+#    #+#             */
/*   Updated: 2019/01/16 17:52:48 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	textures_load(t_app *a)
{
	if (a->p_count <= 0)
		ft_error("Fatal error : invalid file.");
	bmp_loadfile(&a->game_win, "textures/game_win.bmp", 1280, 700);
	bmp_loadfile(&a->game_over, "textures/game_over.bmp", 1280, 700);
	bmp_loadfile(&a->textures[0], "textures/colorstone.bmp", 64, 64);
	bmp_loadfile(&a->textures[1], "textures/greystone.bmp", 64, 64);
	bmp_loadfile(&a->textures[2], "textures/wood.bmp", 64, 64);
	bmp_loadfile(&a->textures[3], "textures/redbrick.bmp", 64, 64);
	bmp_loadfile(&a->textures[4], "textures/purplestone.bmp", 64, 64);
	bmp_loadfile(&a->textures[5], "textures/mossy.bmp", 64, 64);
	bmp_loadfile(&a->textures[6], "textures/window.bmp", 64, 64);
	bmp_loadfile(&a->textures[7], "textures/door1.bmp", 64, 64);
	bmp_loadfile(&a->textures[8], "textures/door2.bmp", 64, 64);
	bmp_loadfile(&a->textures[9], "textures/poster.bmp", 64, 64);
	bmp_loadfile(&a->textures[10], "textures/sky.bmp", 5120, 464);
}

void	sprites_load(t_app *a)
{
	bmp_loadfile(&a->sprites[0], "sprites/zombie1.bmp", 64, 64);
	bmp_loadfile(&a->sprites[1], "sprites/zombie2.bmp", 64, 64);
	bmp_loadfile(&a->sprites[2], "sprites/zombie3.bmp", 64, 64);
	bmp_loadfile(&a->sprites[3], "sprites/zombie4.bmp", 64, 64);
	bmp_loadfile(&a->sprites[4], "sprites/barril.bmp", 64, 64);
	bmp_loadfile(&a->sprites[5], "sprites/pillar.bmp", 64, 64);
	bmp_loadfile(&a->sprites[6], "sprites/skull1.bmp", 64, 64);
	bmp_loadfile(&a->sprites[7], "sprites/skull2.bmp", 64, 64);
	bmp_loadfile(&a->sprites[8], "sprites/skull3.bmp", 64, 64);
	bmp_loadfile(&a->sprites[9], "sprites/skull4.bmp", 64, 64);
	bmp_loadfile(&a->sprites[10], "sprites/dying1.bmp", 64, 64);
	bmp_loadfile(&a->sprites[11], "sprites/dying2.bmp", 64, 64);
	bmp_loadfile(&a->sprites[12], "sprites/dying3.bmp", 64, 64);
	bmp_loadfile(&a->sprites[13], "sprites/dying4.bmp", 64, 64);
	bmp_loadfile(&a->sprites[14], "sprites/dying5.bmp", 64, 64);
	bmp_loadfile(&a->sprites[15], "sprites/dying6.bmp", 63, 64);
	bmp_loadfile(&a->weapon.img, "sprites/ak47.bmp", 556, 326);
	bmp_loadfile(&a->weapon.img2, "sprites/ak47fired.bmp", 556, 326);
	bmp_loadfile(&a->weapon.scope, "sprites/scope.bmp", 128, 128);
}
