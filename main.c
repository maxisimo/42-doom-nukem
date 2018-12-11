/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:58:24 by maxisimo          #+#    #+#             */
/*   Updated: 2018/12/11 16:28:14 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static int	is_extension_valid(char *fname)
{
	if (ft_strncmp(ft_strrev(fname), "d3w.", 4) == 0)
		return (1);
	else
		return (0);
}

int         main(int ac, char **av)
{
    t_e     e;

	if (ac == 2 && is_extension_valid(ft_strdup(av[1])) == 1)
    {
	    ft_bzero(&e, sizeof(t_e));
        e.file = av[1];
    }
    e.cam.dir.x = 1;
    e.cam.plane.y = 0.6;
    ft_mlx(&e);
    return (0);
}