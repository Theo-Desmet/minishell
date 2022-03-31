/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:59:53 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/28 17:01:16 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;

void		ft_putnbr(int n);
void		ft_putchar(char c);
void		ft_putstr(char *str);
void		ft_putnbr_fd(int n, int fd);
void		ft_lstdel_all(t_list **lst);
void		ft_bzero(void *s, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		*ft_memset(void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strlen(char *str);
int			ft_lstsize(t_list *lst);
int			ft_atoi(const char *nptr);
int			ft_atoi_hex(char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dst, char *src, size_t size);
size_t		ft_strlcat(char *dst, char *src, size_t size);
char		*ft_itoa(int n);
char		*ft_strdup(char *s);
char		*ft_strchr(char *s, int c);
char		*ft_strrchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strnstr(const char *s1, const char *s2, size_t len);
char		*ft_strmapi(char *s, char (*f)(unsigned int, char));
char		*ft_substr(char *s, int start, int len);
char		**ft_split(const char *str, char c);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_get_next_line(int fd);
t_list		*ft_lstnew(char *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
