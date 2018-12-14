/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 11:41:56 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/05 11:44:24 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_maping.h"

static void	ft_free_strsplit(char **array)
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
		ft_putendl("Fail to read file");
	while ((get_next_line(fd, &s)) > 0)
	{
		array = ft_strsplit(s, ' ');
		free(s);
		count[1] = 0;
		while (array[count[1]])
			count[1]++;
		if (count[1] > count[2])
			count[2] = count[1];
		ft_free_strsplit(array);
		count[0]++;
	}
	free(s);
	map->width = count[2];
	map->height = count[0];
}

void		allocmap(t_map *map)
{
	int		i;

	i = 0;
	if (!(map->map = (int**)malloc(sizeof(int*) * map->height / map->bloc)))
	{
		ft_putendl("fail to malloc tab");
		exit(-1);
	}
	while (i < map->height / map->bloc)
	{
		if (!(map->map[i] = (int*)malloc(sizeof(int) * map->width / map->bloc)))
		{
			ft_putendl("fail to malloc tab");
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
		ft_putendl("Fatal error : invalid file.");
	while ((get_next_line(fd, &s)) > 0 && map->p.y < map->height / map->bloc)
	{
		map->p.x = 0;
		array = ft_strsplit(s, ' ');
		free(s);
		while (map->p.x < map->width / map->bloc)
		{
			if (array[map->p.x])
				map->map[map->p.y][map->p.x] = ft_atoi(array[map->p.x]);
			else
				map->map[map->p.y][map->p.x] = 0;
			map->p.x++;
		}
		ft_free_strsplit(array);
		map->p.y++;
	}
	free(s);
	close(fd);
}

void		init(t_map *map)
{
	countmap(map);
	map->bloc = (map->height > 58) ? 14 : 24;
	map->width *= map->bloc;
	map->height *= map->bloc;
	allocmap(map);
	writemap(map);
}
