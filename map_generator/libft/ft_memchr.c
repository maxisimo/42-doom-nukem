/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:36:25 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/15 19:50:35 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *c_s;

	c_s = (unsigned char*)s;
	while (n > 0)
	{
		if (*c_s == (unsigned char)c)
			return (c_s);
		c_s++;
		n--;
	}
	return (0);
}
