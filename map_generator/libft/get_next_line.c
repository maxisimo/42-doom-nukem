/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxisimo <maxisimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 12:57:35 by thbernar          #+#    #+#             */
/*   Updated: 2019/01/08 17:57:04 by maxisimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static int	ft_strclen(char *s, char c)
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
}*/
static char	*ft_strnapp(char **str, char *to_add, size_t n)
{
	char	*res;
	size_t	len;

	len = ft_strlen(*str);
	if ((res = (char *)malloc(len + n + 1)) == NULL)
		return (NULL);
	res[len + n] = '\0';
	while (n--)
		res[len + n] = to_add[n];
	while (len--)
		res[len] = (*str)[len];
	free(*str);
	*str = res;
	return (res);
}

static int	get_next_line_return(char **line, char **s, char *nl)
{
	if (nl != NULL)
	{
		if ((*line = ft_strndup(*s, (size_t)nl - (size_t)*s)) == NULL)
			return (-1);
		ft_memmove(*s, nl + 1, ft_strlen(nl));
		return (1);
	}
	if (*s && (*s)[0])
	{
		if ((*line = ft_strdup(*s)) == NULL)
			return (-1);
		free(*s);
		*s = NULL;
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*s;
	char		buff[BUFF_SIZE];
	char		*nl;
	ssize_t		c;

	if (!line || fd < 0)
		return (-1);
	c = BUFF_SIZE;
	while ((nl = ft_strchr(s, '\n')) == NULL && c == BUFF_SIZE)
	{
		ft_memset(buff, 0, BUFF_SIZE);
		if ((c = read(fd, buff, BUFF_SIZE)) > 0)
			if (ft_strnapp(&s, buff, c) == NULL)
				return (-1);
	}
	if (c < 0)
		return (-1);
	return (get_next_line_return(line, &s, nl));
}
