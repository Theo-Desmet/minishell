/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:31:05 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/13 15:55:04 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "struct.h"
# include "stdio.h"

void    ft_expand(t_token **tokens, t_list **env, t_list **wd);
char    *ft_expand_wildcard(t_list **wd, char *val, t_list **env);
char    *ft_not_wd(char *val, char **temp);
char    *ft_expand_str(t_list **env, char *str);
char    **ft_init_expand(char **res, char *str, t_temp *temp, t_list    **env);

char    ft_get_inverted_quote(char *str);
char    *ft_frame_str(char *str, char c);
char    *ft_copy_quotes(char *res, t_temp *temp);
char    ft_get_inverted_quote(char *str);
char    *ft_frame_str(char *str, char c);
char    *ft_copy_quotes(char *res, t_temp *temp);

char    *ft_var(char *res, t_temp *temp);
char    *ft_str_var(char *res, t_temp *temp);
char    *ft_get_str(char *str, int mode);
char    *ft_get_var(t_list **env, char *str);
char    **ft_extract_var(char *str);

size_t  ft_count_vars(char *str);
size_t  ft_len_vars(char *str, size_t i);
char    *ft_charjoin(char *str, char c);
void    ft_init_temp(t_temp *temp, char **vars, char *str, t_list **env);
int     ft_valid_var_char(int c);

#endif
