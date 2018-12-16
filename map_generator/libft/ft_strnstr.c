/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:56:56 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/15 18:47:35 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *to_find, size_t len)
{
	int i;
	int j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char*)s);
	while (s[i] && (size_t)i < len)
	{
		j = 0;
		while (s[i + j] == to_find[j] && (size_t)(i + j) < len)
		{
			if (to_find[j + 1] == '\0')
				return ((char*)s + i);
			j++;
		}
		i++;
	}
	return (0);
}
