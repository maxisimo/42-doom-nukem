/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:46:56 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/14 20:24:30 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *c1;
	const unsigned char *c2;

	c1 = s1;
	c2 = s2;
	while (n > 0)
	{
		if (*c1 != *c2)
			return ((int)(*c1 - *c2));
		c1++;
		c2++;
		n--;
	}
	return (0);
}
