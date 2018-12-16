/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 12:57:35 by thbernar          #+#    #+#             */
/*   Updated: 2017/12/21 13:04:41 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strclen(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_read_fd(const int fd, char **s)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = 0;
		tmp = *s;
		*s = ft_strjoin(*s, buff);
		free(tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && *s[0] == '\0')
		return (0);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*s[OPEN_MAX];
	char		*tmp;
	int			ret;
	int			f_endline;

	if (fd < 0 || fd > OPEN_MAX || line == NULL)
		return (-1);
	if (s[fd] == NULL && !(s[fd] = ft_strnew(1)))
		return (-1);
	if ((ret = ft_read_fd(fd, &s[fd])) == -1)
		return (-1);
	f_endline = ft_strclen(s[fd], '\n');
	if (!(*line = ft_strsub(s[fd], 0, f_endline)))
		return (-1);
	tmp = s[fd];
	s[fd] = ft_strsub(s[fd], f_endline + 1, ft_strlen(s[fd]) - f_endline);
	if (!(s[fd]))
		return (-1);
	free(tmp);
	return (ret);
}
