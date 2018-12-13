/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 20:14:32 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/13 17:03:14 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int		ft_close(t_app *app)
{
	free(app->map);
	exit(0);
	return (0);
}

void	ft_error(char *s)
{
	ft_putstr(s);
	exit(-1);
}

void	ft_free_strsplit(char **array)
{
	int i;

	i = 0;
	while (array	[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_init_tex_fc(t_app *a)
{
	if (a->side == 0 && a->ray.dir.x > 0)
	{
		a->floor_x = a->mapx;
		a->floor_y = a->mapy + a->wallx;
	}
	else if (a->side == 0 && a->ray.dir.x < 0)
	{
		a->floor_x = a->mapx + 1.0;
		a->floor_y = a->mapy + a->wallx;
	}
	else if (a->side == 1 && a->ray.dir.y > 0)
	{
		a->floor_x = a->mapx + a->wallx;
		a->floor_y = a->mapy;
	}
	else
	{
		a->floor_x = a->mapx + a->wallx;
		a->floor_y = a->mapy + 1.0;
	}
	if (a->end < 0)
		a->end = WIN_H;
}
