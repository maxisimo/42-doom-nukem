/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:48:14 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/15 14:34:10 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list *new_lst;

	if (!(new_lst = (t_list*)malloc(sizeof(*new_lst))))
		return (NULL);
	if (content == NULL)
	{
		new_lst->content = NULL;
		new_lst->content_size = 0;
	}
	else
	{
		if (!(new_lst->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(new_lst->content, content, content_size);
		new_lst->content_size = content_size;
	}
	new_lst->next = NULL;
	return (new_lst);
}
