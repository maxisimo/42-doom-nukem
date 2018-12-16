/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:05:43 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/15 19:01:23 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char *dst, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (!dst[	i])
			return (i);
		i++;
	}
	return (size);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;
	size_t	ret;

	i = 0;
	if (size <= (ft_strnlen(dst, size) + 1))
		return (ft_strnlen(dst, size) + ft_strlen((src)));
	len = ft_strlen(dst);
	ret = len + ft_strlen(src);
	while (src[i] != '\0')
	{
		if (len < size - 1)
		{
			dst[len] = src[i];
			len++;
		}
		i++;
	}
	dst[len] = '\0';
	return (ret);
}
