/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:41:56 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/18 14:15:14 by maxisimo         ###   ########.fr       */
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

static void	countmap(t_map *map)
{
	int		fd;
	int		count[3];
	char	*s;
	char	**array;

	count[2] = 0;
	count[0] = 0;
	if (((fd = open(map->name, O_RDONLY)) < 0))
		ft_error("Fail to read file");
	while ((get_next_line(fd, &s)) > 0)
	{
		array = ft_strsplit(s, ' ');
		free(s);
		count[1] = 0;
		while (array[count[1]])
			count[1]++;
		if (count[1] > count[2])
			count[2] = count[1];
		free_strsplit(array);
		count[0]++;
	}
	free(s);
	if (count[2] > 55 || count[0] > 55)
		ft_error("File is to big to be edited");
	map->width = count[2];
	map->height = count[0];
}

void		allocmap(t_map *map)
{
	int		i;

	i = 0;
	if (!(map->map = (int**)malloc(sizeof(int*) * map->height / map->bloch)))
	{
		ft_error("fail to malloc tab");
		exit(-1);
	}
	while (i < map->height / map->bloch)
	{
		if (!(map->map[i] = (int*)malloc(sizeof(int) * map->width / map->blocw)))
		{
			ft_error("fail to malloc tab");
			exit(-1);
		}
		i++;
	}
}

void		writemap(t_map *map)
{
	int		fd;
	char	**array;
	char	*s;

	map->p.y = 0;
	if (((fd = open(map->name, O_RDONLY)) < 0))
		ft_error("Fatal error : invalid file.");
	while ((get_next_line(fd, &s)) > 0 && map->p.y < map->height / map->bloch)
	{
		map->p.x = 0;
		array = ft_strsplit(s, ' ');
		free(s);
		while (map->p.x < map->width / map->blocw)
		{
			if (array[map->p.x])
				map->map[map->p.y][map->p.x] = ft_atoi(array[map->p.x]);
			else
				map->map[map->p.y][map->p.x] = 0;
			map->p.x++;
		}
		free_strsplit(array);
		map->p.y++;
	}
	free(s);
	close(fd);
}

void		init(t_map *map)
{
	countmap(map);
	map->blocw = 1320 / map->width;
	map->bloch = 1320 / map->height;
	map->width *= map->blocw;
	map->height *= map->bloch;
	allocmap(map);
	writemap(map);
}
