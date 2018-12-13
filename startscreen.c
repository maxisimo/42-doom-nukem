/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startscreen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 17:30:54 by thbernar          #+#    #+#             */
/*   Updated: 2018/12/13 16:49:34 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void startscreen_draw(t_app *a)
{
    t_color	c1;
	t_coord tmp;
	double	sin_factor;

    a->loop = a->loop + 0.02;
    sin_factor = fabs(sin(a->loop));
    c1.r = sin_factor * 255;
    c1.g = sin_factor * 255;
    c1.b = sin_factor * 255;
    a->logo.scale = 2 * (sin_factor + 1);
    tmp.x = (WIN_W - a->logo.width * a->logo.scale) / 2;
    tmp.y = (WIN_H - a->logo.height * a->logo.scale) / 2;
    ft_put_bmp_to_img(a, a->logo, tmp.x, tmp.y);
    mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
    mlx_string_put(a->mlx, a->win, WIN_WS, WIN_HS, ft_rgb_to_hex(c1), START);
}
