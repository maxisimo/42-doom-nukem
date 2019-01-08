/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:54:43 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/08 12:01:39 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generator.h"

void		error(void)
{
	ft_putendl("usage: ./map_generator newfile.w3d create");
	ft_putendl("                 or                   ");
	ft_putendl("usage: ./map_generator filename.w3d edit");
}

void		is_edit(char *s, t_map *map)
{
	map->edit = 1;
	map->name = s;
	map->i = 1;
	map->player = 0;
	init(map);
}

void		is_create(char *s, t_map *map)
{
	map->size = 40;
	map->bloc = 1280 / map->size;
	map->size *= map->bloc;
	map->name = s;
	map->i = 1;
	map->player = 0;
	init_tab(map);
}
