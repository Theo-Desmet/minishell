/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:22:24 by bbordere          #+#    #+#             */
/*   Updated: 2021/12/01 11:29:29 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define HEXA_BASE_U "0123456789ABCDEF"
# define HEXA_BASE_L "0123456789abcdef"
# define DECIMAL_BASE "0123456789"
# define NUL_STR "(null)"

# ifdef __linux__
#  define NULL_PTR "(nil)"

# elif
#  ifdef __APPLE__
#   define NULL_PTR "0x0"
#  endif

# else
#  define NULL_PTR "0x0"
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);

int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
int		ft_atol(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_lstsize(t_list *lst);
int		ft_printf(const char *str, ...);
int		ft_strcmp(char *s1, char *s2);
int		ft_isspace(int c);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

ssize_t	ft_get_index(char *str, char c);

void	*ft_memset(void *str, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_putnbr(int n, int *i);
void	ft_putnbr_base(unsigned long n, char *base, int *i);
void	ft_put_address(void	*p, int *i);
void	ft_putstr(char *str, int *i);
void	ft_putchar(int c, int *i);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	*ft_free_tab(void **tab);
void	*ft_realloc(void *ptr, size_t size);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr( const char *str, int c);
char	*ft_strrchr( const char *str, int c);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strdup(const char *source);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin1(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strjoin3(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*get_next_line(int fd);
char	*ft_strreplace(char *old, char *new);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcapitalize(char *str);

#endif
