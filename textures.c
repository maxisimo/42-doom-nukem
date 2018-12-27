/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:54:23 by thbernar          #+#    #+#             */
/*   Updated: 2018/12/27 17:17:05 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	textures_load(t_app *a)
{
	if (a->p_count <= 0)
		ft_error("Fatal error : invalid file.");
	bmp_loadfile(&a->textures[0], "textures/bigdoor.bmp");
	bmp_loadfile(&a->textures[1], "textures/dude.bmp");
	bmp_loadfile(&a->textures[2], "textures/floor.bmp");
	bmp_loadfile(&a->textures[3], "textures/skulwall.bmp");
	bmp_loadfile(&a->textures[4], "textures/marbface.bmp");
	bmp_loadfile(&a->textures[5], "textures/skulwall2.bmp");
	bmp_loadfile(&a->textures[6], "textures/window.bmp");
	bmp_loadfile(&a->textures[7], "textures/door1.bmp");
	bmp_loadfile(&a->textures[8], "textures/door2.bmp");
	//bmp_loadfile(&a->textures[9], "textures/sky1.bmp");
	bmp_loadfile(&a->sprites[0], "sprites/ak47.bmp");
	bmp_loadfile(&a->sprites[1], "sprites/scope.bmp");
}
