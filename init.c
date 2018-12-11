/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:40:56 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/11 19:11:05 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int		ft_close(t_e *e)
{
	ft_free_map(e);
	exit(0);
	return (0);
}

void	ft_start_screen(t_e *e)
{
	t_color	c1;
	t_coord tmp;
	double	sin_factor;

	e->loop = e->loop + 0.02;
	sin_factor = fabs(sin(e->loop));
	c1.r = sin_factor * 255;
	c1.g = sin_factor * 255;
	c1.b = sin_factor * 255;
	e->logo.scale = 2 * (sin_factor + 1);
	tmp.x = (WIN_W - e->logo.width * e->logo.scale) / 2;
	tmp.y = (WIN_H - e->logo.height * e->logo.scale) / 2;
	ft_put_bmp_to_img(e, e->logo, tmp.x, tmp.y);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_string_put(e->mlx, e->win, WIN_WS, WIN_HS, ft_rgb_to_hex(c1), START);
}

void    ft_mlx(t_e *e)
{
    e->mlx = mlx_init();
    e->win = mlx_new_window(e->mlx, WIN_W, WIN_H, "Doom-Nukem");
    bmp_loadfile(&e->logo, "textures/logo.bmp");
	mlx_hook(e->win, 2, (1L << 0), ft_key_press, e);
	mlx_hook(e->win, 3, (1L << 1), ft_key_release, e);
    mlx_mouse_hide();
	mlx_mouse_move(e->win, WIN_W / 2, WIN_H / 2);
	mlx_hook(e->win, 6, 0, ft_mouse_motion,e);
	mlx_hook(e->win, 17, (1L << 17), ft_close, e);
	mlx_loop_hook(e->mlx, expose_hook, e);
	mlx_loop(e->mlx);
}
