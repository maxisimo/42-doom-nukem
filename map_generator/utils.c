/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:54:43 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/16 15:58:05 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

void	error(void)
{
	ft_putendl("usage: ./generator_maping newfilename [width] [height]");
	ft_putendl("or");
	ft_putendl("usage: ./generator_maping filename");
}

void	argc4(char *s1, char *s2, char *s3, t_map *map)
{
	map->ac = 4;
	map->width = (abs(ft_atoi(s2)) > 95) ? 95 : abs(ft_atoi(s2));
	map->height = (abs(ft_atoi(s3)) > 95) ? 95 : abs(ft_atoi(s3));
	map->bloc = (map->height > 58) ? 14 : 24;
	map->width *= map->bloc;
	map->height *= map->bloc;
	map->name = s1;
	map->i = 0;
	map->player = 0;
}

void	argc2(char *s, t_map *map)
{
	map->ac = 2;
	map->name = s;
	map->i = 0;
	map->player = 0;
}

void	mlx_win_init(t_map *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->width, map->height, map->name);
	map->img = mlx_new_image(map->mlx, map->width, map->height);
	map->img_ptr = mlx_get_data_addr(map->img,
			&map->bpp, &map->sl, &map->endian);
}
