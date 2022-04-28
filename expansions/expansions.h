/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:31:05 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/19 21:31:05 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include "../struct.h"
# include "../lexer/lexer.h"

t_list			**ft_init_env(t_list **env, char **envp);
t_data			*ft_init_data(char **envp);
void			*ft_return_dup(char *str, char *dup);
void			*ft_expand_return_code(char *str);
char			*ft_get_var(t_list **env, char *str);
size_t			ft_count_vars(char *str);
size_t			ft_len_vars(char *str, size_t i);
char			**ft_extract_var(char *str);
char			*ft_charjoin(char *str, char c);
char			*ft_get_str(char *str, int mode);

void			ft_init_temp(t_temp *temp, char **vars,
					char *str, t_list **env);
void			ft_free(void **tab);
char			*ft_var(char *res, t_temp *temp);
char			*ft_str_var(char *res, t_temp *temp);
char			**ft_init_expand(char **res, char *str,
					t_temp *temp, t_list **env);
char			*ft_copy_quotes(char *res, t_temp *temp);
char			*ft_expand_str(t_list **env, char *str);
void			ft_expand(t_token **tokens, t_list **env, t_list **wd);
void			ft_lstdel_all(t_list **lst);
int				ft_isspecchar(int c);
int				ft_ispar(int c);
int				ft_issep(int c);
int				ft_wildcard(t_list **wd, char *str);

#endif