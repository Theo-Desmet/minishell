/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:05:53 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/13 15:40:58 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdio.h>
# include "struct.h"
# include <dirent.h>
# include <ctype.h>

size_t	ft_block_count(char *str);
void	ft_count_var(char *str, size_t *i, size_t *nb);
void	ft_count_word(char *str, size_t *i, size_t *nb);
void	ft_count_word_sep(char *str, size_t *i, int mode);
void	ft_count_word_spec(char *str, size_t *i, size_t *nb);

int		ft_islimit(int type);
char	**ft_join(t_token **tokens);
size_t	ft_count_join(t_token **tokens);
void	ft_skip_sep(char *str, size_t *i);
char	**ft_regroup_tokens(t_token **tokens, size_t *i, size_t *j, char **res);

int		ft_iswildcard(char *val);
t_token	*ft_init_token(char *val);
t_token	**ft_tokenize(char **tab);
int		ft_init_op(t_token *token, char *val);
void	ft_skip_quotes(char *val, ssize_t *i);

int		ft_issep(int c);
int		ft_ispar(int c);
void	ft_free(void **tab);
int		ft_isspecchar(int c);
int		ft_isfulldollar(char *str);
int		ft_strcasecmp(char *s1, char *s2);
void	ft_skip_spaces(char *str, size_t *i);
void	ft_get_count(char *str, size_t *i, size_t *nb);

char	**ft_split_conserve(const char *str, char c);

char	**ft_lexer(char *str);
size_t	ft_size_str(char *str, int i);
size_t	ft_size_var(char *str, size_t i);
size_t	ft_word_size(char *str, size_t i);
void	ft_fill_tab(char *str, size_t *i, size_t *j, char **res);

int		ft_wildcard(t_list **wd, char *str);
int		ft_strstr_len(const char *s1, const char *s2);
void	ft_sort_lst(t_list **wd, int (*comp)(char *, char *));
void	ft_check_wildcard(t_list **wd, char **tab, char *name);
int		ft_check_last_wd(char **tab, char *name, int i, int j);

#endif
