/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:14:39 by thbernar          #+#    #+#             */
/*   Updated: 2017/11/15 19:32:21 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char *s, char c)
{
	int j;

	j = 0;
	while (*s != c && *s)
	{
		j++;
		s++;
	}
	return (j);
}

static int	ft_count(const char *s, char c)
{
	int nb;
	int new_word;

	nb = 0;
	new_word = 0;
	while (*s)
	{
		if (*s == c)
			new_word = 0;
		if (*s != c && new_word == 0)
		{
			new_word = 1;
			nb++;
		}
		s++;
	}
	return (nb);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**array;
	int		i;
	int		nb_words;

	i = 0;
	nb_words = ft_count((char*)s, c);
	array = (char **)malloc(sizeof(char*) * (nb_words + 1));
	if (!array)
		return (NULL);
	while (nb_words--)
	{
		while (*s == c && *s)
			s++;
		if (!(array[i] = ft_strsub(s, 0, ft_size((char*)s, c))))
			return (NULL);
		s = s + ft_size((char*)s, c);
		i++;
	}
	array[i] = NULL;
	return (array);
}
