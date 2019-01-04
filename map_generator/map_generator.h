/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:40:45 by maxisimo          #+#    #+#             */
/*   Updated: 2019/01/04 13:19:18 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_GENERATOR_H
# define MAP_GENERATOR_H

# include "../doom_nukem.h"

typedef struct	s_map
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*img_ptr;
	char		*name;
	int			**map;
	int			endian;
	int			sl;
	int			bpp;
	int			size;
	int			bloc;
	int			x;
	int			y;
	int			i;
	int			player;
	int			edit;
    int		    tempx;
	int		    tempy;
	int		    temp2x;
	int	    	temp2y;
	int	    	n;
	t_coord		p;
	t_bmp		textures[10];
	double		textures_scale;
}				t_map;

void			error(void);
void	        is_edit(char *s, t_map *map);
void        	is_create(char *s, t_map *map);
void			start(t_map *map);

int				key_hook(int keycode, t_map *map);
int				mouse_hook(int mousecode, int x, int y, t_map *map);

void			init(t_map *map);

void			init_tab(t_map *map);
void			fill_tab(int x, int y, int value, t_map *map);

void			infos(t_map *map);
void			put_color2(int x, int y, t_map *map);
void			put_color(int x, int y, t_map *map);
void			draw_map(int x, int y, t_map *map);

#endif
