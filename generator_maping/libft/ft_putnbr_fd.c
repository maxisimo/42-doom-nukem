/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 19:18:15 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/14 11:28:01 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int u_nb;

	u_nb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		u_nb = -n;
	}
	if (u_nb > 9)
	{
		ft_putnbr_fd(u_nb / 10, fd);
		ft_putnbr_fd(u_nb % 10, fd);
	}
	if (u_nb < 10)
	{
		ft_putchar_fd(u_nb + '0', fd);
	}
}
