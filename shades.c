/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shades.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:31:37 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/17 12:32:48 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_apply_shadow_to_cf(t_color *c, int y)
{
	c->r *= (1 - (800. / abs(y)) / 2.);
	c->g *= (1 - (800. / abs(y)) / 2.);
	c->b *= (1 - (800. / abs(y)) / 2.);
	c->r = (c->r < 0) ? 0 : c->r;
	c->g = (c->g < 0) ? 0 : c->g;
	c->b = (c->b < 0) ? 0 : c->b;
}

void	ft_apply_shadow_to_spr(t_color *c, int y)
{
	c->r *= (1 - (1. / (20. / y)) / 2.);
	c->g *= (1 - (1. / (20. / y)) / 2.);
	c->b *= (1 - (1. / (20. / y)) / 2.);
	c->r = (c->r < 0) ? 0 : c->r;
	c->g = (c->g < 0) ? 0 : c->g;
	c->b = (c->b < 0) ? 0 : c->b;
	c->r = (c->r >= 255) ? 255 : c->r;
	c->g = (c->g >= 255) ? 255 : c->g;
	c->b = (c->b >= 255) ? 255 : c->b;
}

void	ft_apply_shadow_to_color(t_color *c, double intensity)
{
	c->r = c->r * intensity;
	c->g = c->g * intensity;
	c->b = c->b * intensity;
}
