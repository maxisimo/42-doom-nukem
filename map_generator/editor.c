/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:41:56 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/16 14:10:34 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

static void	free_strsplit(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	cleanmap(t_map *map)
{
	t_coord p;

	p.x = 0;
	while (p.x < 40)
	{
		p.y = 0;
		while (p.y < 40)
		{
			map->map[p.x][p.y] = 0;
			p.y++;
		}
		p.x++;
	}
}

static void	allocmap(t_map *map)
{
	int		i;

	i = 0;
	if (!(map->map = (int**)malloc(sizeof(int*) * 40)))
	{
		ft_error("Error : Fail to malloc tab");
		exit(-1);
	}
	while (i < 40)
	{
		if (!(map->map[i] = (int*)malloc(sizeof(int) * 40)))
		{
			ft_error("Error : Fail to malloc tab");
			exit(-1);
		}
		i++;
	}
}

static void	writemap(t_map *map)
{
	int		fd;
	char	**array;
	char	*s;

	if (((fd = open(map->name, O_RDONLY)) < 0))
		return ;
	map->p.y = 0;
	while ((get_next_line(fd, &s)) > 0 && map->p.y < map->size / map->bloc)
	{
		map->p.x = 0;
		array = ft_strsplit(s, ' ');
		free(s);
		while (map->p.x < 40 && array[map->p.x])
		{
			if (array[map->p.x])
				map->map[map->p.y][map->p.x] = ft_atoi(array[map->p.x]) % 14;
			map->p.x++;
		}
		free_strsplit(array);
		map->p.y++;
	}
	map->p.x > 1 ? free(s) : 0;
	close(fd);
}

void		init(t_map *map)
{
	map->bloc = 32;
	map->size = 1280;
	map->i = 1;
	map->player = 0;
	allocmap(map);
	cleanmap(map);
	writemap(map);
}
