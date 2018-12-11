/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:50:51 by thbernar          #+#    #+#             */
/*   Updated: 2018/02/12 16:54:17 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H
# define BUFF_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero (void *s, size_t n);
int					ft_isalnum (int c);
int					ft_isalpha (int c);
int					ft_isascii (int c);
int					ft_isdigit (int c);
int					ft_isprint (int c);
char				*ft_itoa (int n);
void				*ft_memalloc (size_t size);
void				*ft_memccpy (void *dest, const void *src, int c, size_t n);
void				*ft_memchr (const void *s, int c, size_t n);
int					ft_memcmp (const void *s1, const void *s2, size_t n);
void				*ft_memcpy (void *dest, const void *src, size_t n);
void				ft_memdel (void **ap);
void				*ft_memmove (void *dest, const void *src, size_t n);
void				*ft_memset (void *s, int c, size_t n);
void				ft_putchar (char c);
void				ft_putchar_fd (char c, int fd);
void				ft_putendl (char const *s);
void				ft_putendl_fd (char const *s, int fd);
void				ft_putnbr (int n);
void				ft_putnbr_fd (int n, int fd);
void				ft_putstr (char const *s);
void				ft_putstr_fd (char const *s, int fd);
char				*ft_strcat (char *dest, const char *src);
char				*ft_strchr (const char *s, int c);
void				ft_strclr (char *s);
int					ft_strcmp (const char *s1, const char *s2);
char				*ft_strcpy (char *dest, const char *src);
void				ft_strdel (char **as);
char				*ft_strdup (const char *src);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ (const char *s1, const char *s2, size_t n);
void				ft_striter (char *s, void (*f)(char *));
void				ft_striteri (char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin (const char *s1, const char *s2);
size_t				ft_strlcat (char *dest, const char *src, size_t n);
size_t				ft_strlen (const char *str);
char				*ft_strmap (char const *s, char (*f)(char));
char				*ft_strmapi (char const *s, char (*f)(unsigned int, char));
char				*ft_strncat (char *dest, const char *src, size_t n);
int					ft_strncmp (const char *s1, const char *s2, size_t n);
char				*ft_strncpy (char *dest, const char *src, size_t n);
char				*ft_strnew (size_t size);
char				*ft_strnstr(const char *s, const char *to_find, size_t len);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit (const char *s, char c);
char				*ft_strstr (const char *str, const char *to_find);
char				*ft_strsub (const char *s, unsigned int start, size_t len);
char				*ft_strtrim(const char *s);
int					ft_tolower (int c);
int					ft_toupper (int c);

t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

char				*ft_strrev(char *str);
int					ft_strisalpha(const char *str);
int					ft_strisnumeric(const char *str);
char				*ft_strcapitalize(char *str);
char				*ft_strtolower(char *str);
int					ft_isprime(int nb);

int					get_next_line(const int fd, char **line);

#endif
