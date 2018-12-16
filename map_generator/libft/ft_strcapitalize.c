/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 16:33:56 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/20 11:13:12 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int i;

	i = 0;
	str = ft_strtolower(str);
	while (str[i])
	{
		if (ft_isalpha(str[i]) && ft_isalnum(str[i - 1]) == 0)
		{
			str[i] = str[i] - 32;
		}
		i++;
	}
	return (str);
}
