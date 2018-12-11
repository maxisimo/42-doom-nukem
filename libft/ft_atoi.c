/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 19:24:54 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/14 11:14:53 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char const *str)
{
	int		is_negative;
	size_t	i;
	size_t	integer;

	is_negative = 0;
	i = 0;
	integer = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') \
		|| (str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		is_negative = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		integer = integer * 10 + (str[i] - '0');
		i++;
	}
	if (is_negative)
		integer = integer * -1;
	return (integer);
}
