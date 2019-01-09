/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:27:34 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/09 15:41:20 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

void		init_tab(t_map *map)
{
	int		i;

	i = 0;
	if (!(map->map = (int**)malloc(sizeof(int*) * map->size / map->bloc)))
	{
		ft_error("Error : Fail to malloc");
		exit(-1);
	}
	while (i < map->size / map->bloc)
	{
		if (!(map->map[i] = (int*)malloc(sizeof(int) * map->size / map->bloc)))
		{
			ft_error("Error : Fail to malloc");
			exit(-1);
		}
		ft_bzero(map->map[i], sizeof(int) * (map->size / map->bloc));
		i++;
	}
}

void		map_save(t_map *map)
{
	int		i;
	int		j;
	int		fd;
	char	s[map->size];

	i = 0;
	if (((fd = open(map->name, O_CREAT | O_WRONLY, 0644)) < 0))
		ft_error("Error : File not create correctly");
	while (i < map->size / map->bloc)
	{
		j = -1;
		while (++j < map->size / map->bloc)
		{
			s[j] = (abs(map->map[i][j] % 10) + 48);
			if (map->map[i][j] < 0)
				ft_putchar_fd('-', fd);
			ft_putchar_fd(s[j], fd);
			ft_putchar_fd(' ', fd);
		}
		if (i + 1 != map->size / map->bloc)
			ft_putchar_fd('\n', fd);
		i++;
	}
	close(fd);
}
