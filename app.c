/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:06:47 by lchappon          #+#    #+#             */
/*   Updated: 2019/01/10 19:04:46 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	ft_app_countmap(t_app *app)
{
	int		count[4];
	char	*s;
	char	**array;

	count[2] = 0;
	count[0] = 0;
	if (((count[3] = open(app->fname, O_RDONLY)) < 0))
		ft_error("Error : invalid file.");
	while ((get_next_line(count[3], &s)) > 0)
	{
		array = ft_strsplit(s, ' ');
		free(s);
		count[1] = 0;
		while (array[count[1]])
			count[1]++;
		count[1] >= count[2] ? count[2] = count[1] :
			ft_error("Error : Invalid file.");
		ft_free_strsplit(array);
		count[0]++;
		if (count[0] > 100 || count[2] > 100)
			ft_error("Fatal error : invalid file.");
	}
	count[2] > 0 ? free(s) : 0;
	app->map_size.x = count[2] + 2;
	app->map_size.y = count[0] + 2;
}

void		ft_app_allocmap(t_app *app)
{
	int		i;
	t_coord	p;

	i = 0;
	if (!(app->map = (int**)malloc(sizeof(int*) * app->map_size.x)))
		exit(-1);
	while (i < app->map_size.x)
	{
		if (!(app->map[i] = (int*)malloc(sizeof(int) * app->map_size.y)))
			exit(-1);
		i++;
	}
	p.y = 0;
	while (p.y < app->map_size.y)
	{
		p.x = -1;
		while (++p.x < app->map_size.x)
			app->map[p.x][p.y] = 1;
		p.y++;
	}
}

void		ft_app_writemap(t_app *app)
{
	int		fd;
	char	**arr;
	char	*s;
	t_coord p;

	p.y = 1;
	if (((fd = open(app->fname, O_RDONLY)) < 0))
		ft_error("Fatal error : invalid file.");
	while ((get_next_line(fd, &s)) > 0 && p.y < app->map_size.y - 1)
	{
		p.x = 0;
		arr = ft_strsplit(s, ' ');
		free(s);
		while (p.x < app->map_size.x - 2 && arr[p.x] != NULL)
		{
			if (arr[p.x] && -1 <= ft_atoi(arr[p.x]) && ft_atoi(arr[p.x]) < 64)
				app->map[p.x + 1][p.y] = ft_atoi(arr[p.x]);
			p.x++;
		}
		ft_free_strsplit(arr);
		p.y++;
	}
	p.x > 1 ? free(s) : 0;
}

static void	ft_app_calcplayerpos(t_app *app)
{
	t_coord p;

	p.y = 0;
	while (p.y < app->map_size.y)
	{
		p.x = 0;
		while (p.x < app->map_size.x)
		{
			if (app->map[p.x][p.y] == -1)
			{
				app->pos.y = (double)p.y + 0.5;
				app->pos.x = (double)p.x + 0.5;
				app->map[p.x][p.y] = 0;
				app->p_count++;
			}
			p.x++;
		}
		p.y++;
	}
}

void		ft_app_init(t_app *app)
{
	ft_app_countmap(app);
	ft_app_allocmap(app);
	ft_app_writemap(app);
	ft_app_calcplayerpos(app);
	enemies_init(app);
	textures_load(app);
	app->life = 100;
	app->life2 = app->life;
	app->ammo = 90;
}
