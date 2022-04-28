/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:05:53 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/25 11:05:53 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include "../struct.h"
# include <dirent.h>

int		ft_isspecchar(int c);
int		ft_issep(int c);
int		ft_ispar(int c);
void	ft_skip_spaces(char *str, size_t *i);
void	ft_count_word_sep(char *str, size_t *i, int mode);
void	ft_count_word_spec(char *str, size_t *i, size_t *nb);
void	ft_count_word(char *str, size_t *i, size_t *nb);
size_t	ft_block_count(char *str);
int		ft_init_op(t_token *token, char *val);
t_token	*ft_init_token(char *val);
t_token	**ft_tokenize(char **tab);
void	ft_free(void **tab);
size_t	ft_size_var(char *str, size_t i);
char	**ft_lexer(char *str);
char	**ft_join(t_token **tokens);
size_t	ft_tab_size(t_token	**tokens);
void	ft_skip_sep(char *str, size_t *i);

#endif