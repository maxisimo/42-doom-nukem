/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:19:08 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/10 14:28:05 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *m;

	m = (char*)malloc(sizeof(m) * size);
	if (m == NULL)
		return (0);
	ft_bzero(m, size);
	return (m);
}
