/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:32:43 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/14 11:19:48 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		len;
	char	*s1;

	i = 0;
	len = 0;
	len = ft_strlen((char*)s);
	s1 = ft_strnew(len);
	if (s1 == NULL)
		return (NULL);
	while (s[i])
	{
		s1[i] = (*f)(s[i]);
		i++;
	}
	return (s1);
}
