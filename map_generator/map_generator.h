/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:40:45 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/16 14:26:00 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_GENERATOR_H
# define MAP_GENERATOR_H

# include "../doom_nukem.h"

# define TIP1 "Press 'tab' to change texture"
# define TIP2 "Press 's' to save and 'esc' to quit"
# define TIP3 "Press 'P' to activate/desactivate the player position"
# define TIP4 "Press the left mouse button to put a wall / player position"
# define TIP5 "Press the right mouse button to take off wall / player position"

typedef struct	s_map
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*img_ptr;
	char		*name;
	int			**map;
	int			size;
	int			bloc;
	int			x;
	int			y;
	int			i;
	int			player;
	int			edit;
	int			tempx;
	int			tempy;
	int			temp2x;
	int			temp2y;
	int			n;
	t_coord		p;
	t_coord		tmp;
	t_bmp		textures[13];
}				t_map;

void			is_edit(char *s, t_map *map);
void			is_create(char *s, t_map *map);
void			start(t_map *map);

int				key_hook(int keycode, t_map *map);
int				mouse_hook(int mousecode, int x, int y, t_map *map);

void			init(t_map *map);

void			init_tab(t_map *map);
void			map_save(t_map *map);

void			put_color2(int x, int y, t_map *map);
void			put_color(int x, int y, t_map *map);

void			put_px_to_img(t_map *map, int x, int y, int color);
void			ft_put_bmp(t_map *map, t_bmp bmp, int x, int y);
void			infos(t_map *map);

int				draw(t_map *map);

#endif
