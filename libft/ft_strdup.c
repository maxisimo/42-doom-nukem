/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 12:33:35 by thbernar          #+#    #+#             */
/*   Updated: 2019/01/09 16:59:42 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(src);
	dest = NULL;
	dest = (char*)malloc(sizeof(*dest) * len + 1);
	if (dest == NULL)
		return (NULL);
	while (++i < len)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
