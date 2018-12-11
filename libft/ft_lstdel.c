/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:48:52 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/15 19:56:28 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *lst;
	t_list *next_lst;

	lst = *alst;
	while (lst)
	{
		next_lst = lst->next;
		del(lst->content, lst->content_size);
		free(lst);
		lst = next_lst;
	}
	*alst = NULL;
}
