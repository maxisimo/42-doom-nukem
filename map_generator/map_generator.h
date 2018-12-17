/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:40:45 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/17 19:07:43 by maxisimo         ###   ########.fr       */
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
	int			width;
	int			height;
	int			bloc;
	int			x;
	int			y;
	int			i;
	int			player;
	int			but1;
	int			but2;
	int			ac;
    int		    tempx;
	int		    tempy;
	int		    temp2x;
	int	    	temp2y;
	int	    	n;
	t_coord		p;
}				t_map;

void			mlx_win_init(t_map *map);
void			init(t_map *map);
void			draw_grill(int x, int y, t_map *map);
void			init_tab(t_map *map);
void			put_color(int x, int y, t_map *map);
void			fill_tab(int x, int y, int value, t_map *map);
void			put_color2(int x, int y, t_map *map);

int				key_hook(int keycode, t_map *map);
int				but_press(int mousecode, t_map *map);
int				but_release(int mousecode, t_map *map);
int				mouse_hook(int mousecode, int x, int y, t_map *map);

void			error(void);
void	        argc2(char *s, t_map *map);
void        	argc4(char *s1, char *s2, char *s3, t_map *map);

#endif
