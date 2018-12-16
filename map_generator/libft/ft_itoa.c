/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:53:52 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/15 19:31:45 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countdigit(int n, int sign)
{
	int i;

	i = 1;
	while (n <= (-10))
	{
		n = n / 10;
		i++;
	}
	if (sign == (-1))
		i++;
	return (i);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	ft_getsign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		sign;
	int		i;

	sign = ft_getsign(n);
	n = ft_abs(n) * (-1);
	i = ft_countdigit(n, sign);
	if ((s = ft_strnew(i)) == NULL)
		return (NULL);
	s[i] = '\0';
	i--;
	while ((i >= 0 && sign == 1) || (i > 0 && sign == (-1)))
	{
		s[i] = (ft_abs(n % 10)) + 48;
		n = n / 10;
		i--;
	}
	if (sign == (-1))
		s[i] = '-';
	return (s);
}
