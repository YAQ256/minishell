/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:01:23 by cyacoub-          #+#    #+#             */
/*   Updated: 2023/09/04 16:35:37 by cyacoub-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define RED     "\x1b[31m"
# define RESET   "\x1b[0m"
# include "../minishell.h"
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_lst
{
	char			*data;
	struct s_lst	*next;
}	t_lst;

int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
void		*ft_memset(void *b, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *str, const char *to_find, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_putendl_fd(char *s, int fd);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		**ft_split(char const *s, char c);
t_lst		*ft_lstnew(char *data);
void		ft_lstadd_front(t_lst **lst, t_lst *new);
int			ft_lstsize(t_lst *lst);
void		ft_lstadd_back(t_lst **lst, t_lst *new);
t_lst		*ft_lstlast(t_lst *lst);
void		ft_lstdelone(t_lst *lst, void (*del)(char*));
void		ft_lstclear(t_lst **lst, void (*del)(char*));
void		ft_lstiter(t_lst *lst, void *(*f)(char*));
t_lst		*ft_lstmap(t_lst *lst, char *(f)(char*), void (*del)(char*));
t_lst		*ft_lstseclast(t_lst *lst);
int			ft_issign(char c);
int			ft_isspace(char c);
void		ft_swap(int *a, int *b);
int			ft_strcmp(const char *s1, const char *s2);
long long	ft_atoll(const char *str);
void		*ft_memdel(void *ptr);

#endif
