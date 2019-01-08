/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 17:30:54 by thbernar          #+#    #+#             */
/*   Updated: 2019/01/08 17:03:09 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	startscreen_draw(t_app *a)
{
	int		clr;
	t_color	c1;
	t_coord	tmp;
	double	sin_factor;

	if (a->startscreen == 1)
	{
		a->loop = a->loop + 0.02;
		sin_factor = fabs(sin(a->loop));
		c1.r = sin_factor * 255;
		c1.g = sin_factor * 255;
		c1.b = sin_factor * 255;
		clr = ft_rgb_to_hex(c1);
		a->logo.scale = 0.75 * (sin_factor + 1);
		tmp.x = (WIN_W - a->logo.width * a->logo.scale) / 2;
		tmp.y = (WIN_H - a->logo.height * a->logo.scale) / 2;
		ft_put_bmp_to_img(a, a->logo, tmp.x, tmp.y);
		mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
		mlx_string_put(a->mlx, a->win, WIN_WS, WIN_HS, clr, START);
	}
	else
		story(a);
}

void	story(t_app *a)
{
	mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
	mlx_string_put(a->mlx, a->win, 400, 80, 0xFFFFFF, SENTENCE1);
	mlx_string_put(a->mlx, a->win, 400, 160, 0xFFFFFF, SENTENCE2);
	mlx_string_put(a->mlx, a->win, 400, 240, 0xFFFFFF, SENTENCE3);
	mlx_string_put(a->mlx, a->win, 400, 320, 0xFFFFFF, SENTENCE4);
	mlx_string_put(a->mlx, a->win, 400, 400, 0xFFFFFF, SENTENCE5);
	mlx_string_put(a->mlx, a->win, 400, 480, 0xFFFFFF, SENTENCE6);
	mlx_string_put(a->mlx, a->win, 400, 560, 0xFFFFFF, SENTENCE7);
	mlx_string_put(a->mlx, a->win, 400, 640, 0xFFFFFF, SENTENCE8);
}

void	game_over(t_app *a)
{
	if (a->life > 0)
	{
		ft_put_bmp_to_img(a, a->game_win, 0, 0);
		mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
	}
	else
	{
		ft_put_bmp_to_img(a, a->game_over, 0, 0);
		mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
	}
}
