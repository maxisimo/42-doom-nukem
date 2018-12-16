/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_maping.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:27:34 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/16 15:58:52 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

void		init_tab(t_map *map)
{
	int		i;

	i = 0;
	if (!(map->map = (int**)malloc(sizeof(int*) * map->height / map->bloc)))
	{
		ft_putendl("fail to malloc");
		exit(-1);
	}
	while (i < map->height / map->bloc)
	{
		if (!(map->map[i] = (int*)malloc(sizeof(int) * map->width / map->bloc)))
		{
			ft_putendl("fail to malloc");
			exit(-1);
		}
		ft_bzero(map->map[i], sizeof(int) * (map->width / map->bloc));
		i++;
	}
}

void		fill_tab(int x, int y, int value, t_map *map)
{
	int		i;
	int		j;
	int		fd;
	char	s[map->width];

	i = 0;
	map->map[y][x] = value;
	if (((fd = open(map->name, O_CREAT | O_WRONLY, 446)) < 0))
		ft_putendl("File not create correctly");
	while (i < map->height / map->bloc)
	{
		j = -1;
		while (++j < map->width / map->bloc)
		{
			s[j] = (abs(map->map[i][j] % 10) + 48);
			if (map->map[i][j] < 0)
				ft_putchar_fd('-', fd);
			ft_putchar_fd(s[j], fd);
			ft_putchar_fd(' ', fd);
		}
		if (i + 1 != map->height / map->bloc)
			ft_putchar_fd('\n', fd);
		i++;
	}
	close(fd);
}
