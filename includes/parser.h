/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:20:53 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/21 11:56:03 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"
# include "libft.h"
# include "lexer.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define ERROR_MSG "minishell: syntax error near unexpected token "

int		ft_check_op(t_token **tokens, size_t	i);
int		ft_isvalidtype(int type);
size_t	ft_tab_size(t_token	**tokens);
int		ft_isop(int type);
int		ft_check_grammar(t_token **tokens);
int		ft_check_quotes(t_token	*token, char *quote);
int		ft_check_here_doc(t_token **tokens, size_t i);
int     ft_check_builtin(t_data *data, t_token **args);
void	ft_get_cmd(char **command);
int     ft_exec_builtin(t_data *data, t_token **args);
size_t	ft_count_pipes(t_token	**tokens, size_t *offset);
void	ft_pipeline(t_data *data, t_token **tokens);
char	**ft_lst_to_tab(t_list **lst);
char	*ft_check_last_heredoc(t_data *data, t_token **args);
void	ft_redirection(t_data *data, t_token **args, int index);
void	ft_rd_in(t_data *data, char *arg, int i);
char	*ft_join_word(t_token **args);
void	ft_exec(t_list **env, char *arg);
void	ft_find_heredoc(t_data *data, t_token **args);
int     ft_cd(t_data *data, char **str);
int     ft_echo(char **args);
int     ft_env(t_list **env);
int	ft_export(t_list **env, char **arg);
int     ft_pwd(t_data *data);
int	ft_unset(t_list **env, char **arg);




#endif