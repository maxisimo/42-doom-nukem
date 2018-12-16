/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 19:18:15 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/08 17:27:43 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int u_nb;

	u_nb = n;
	if (n < 0)
	{
		ft_putchar('-');
		u_nb = -n;
	}
	if (u_nb > 9)
	{
		ft_putnbr(u_nb / 10);
		ft_putnbr(u_nb % 10);
	}
	if (u_nb < 10)
	{
		ft_putchar(u_nb + '0');
	}
}
