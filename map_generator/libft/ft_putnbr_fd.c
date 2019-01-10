/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 19:18:15 by thbernar          #+#    #+#             */
/*   Updated: 2019/01/10 13:45:40 by maxisimo         ###   ########.fr       */
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
