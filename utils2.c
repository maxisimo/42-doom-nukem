/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:09:25 by lchappon          #+#    #+#             */
/*   Updated: 2018/12/16 16:09:26 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
	while (array[i])
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
		a->floor.x = a->mapx;
		a->floor.y = a->mapy + a->wallx;
	}
	else if (a->side == 0 && a->ray.dir.x < 0)
	{
		a->floor.x = a->mapx + 1.0;
		a->floor.y = a->mapy + a->wallx;
	}
	else if (a->side == 1 && a->ray.dir.y > 0)
	{
		a->floor.x = a->mapx + a->wallx;
		a->floor.y = a->mapy;
	}
	else
	{
		a->floor.x = a->mapx + a->wallx;
		a->floor.y = a->mapy + 1.0;
	}
	if (a->end < 0)
		a->end = WIN_H;
}
