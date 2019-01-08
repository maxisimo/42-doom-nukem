/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:22:11 by thbernar          #+#    #+#             */
/*   Updated: 2019/01/08 16:06:27 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;
	char	*s3;

	i = 0;
	len_s1 = ft_strlen((char*)s1);
	len_s2 = ft_strlen((char*)s2);
	if (!(s3 = (char*)malloc(sizeof(*s3) * (len_s1 + len_s2 + 1))));
		return (0);
	while (i < len_s1)
	{
		s3[i] = s1[i];
		i++;
	}
	i = 0;
	while (len_s1 + i < len_s1 + len_s2)
	{
		s3[len_s1 + i] = s2[i];
		i++;
	}
	s3[len_s1 + i] = '\0';
	return (s3);
}
