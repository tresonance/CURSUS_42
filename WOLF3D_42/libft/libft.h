/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:26:12 by ibtraore          #+#    #+#             */
/*   Updated: 2016/11/22 02:35:38 by ibtraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	int				content_size;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *str, int c, size_t n);
void				ft_bzero(void *str, size_t n);
int					ft_max(int a, int b);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dest, const void *src, size_t len);
int					ft_memcmp(const void *s, const void *s2, size_t len);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				*ft_memchr(const void *s, int c, size_t len);
size_t				ft_strlen(const char *str);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, size_t n);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strnew(size_t n);
void				ft_strclr(char *str);
void				ft_strdel(char **ref);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *str, int c);
char				*ft_strtrim(char const *s);
char				*ft_strnjoin(const char *s1, const char *s2, size_t n);
int					ft_abs(int i);
char				*ft_strnstr(const char *big, const char *little, size_t n);
void				ft_putchar (char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
int					ft_iswhitespace(int c);
int					ft_isdigit(int c);
int					ft_atoi (char *str);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strstr(const char *s1, const char *s2);
size_t				ft_countwords(char *str, char sep);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii (int c);
int					ft_isprint(int c);
char				*ft_strmerge(char *s1, char *s2);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strrchr(const char *str, int c);

#endif
