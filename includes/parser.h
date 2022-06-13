/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:20:53 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/13 17:17:35 by bbordere         ###   ########.fr       */
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
# define ERROR_QUOTE "minishell: unexpected EOF while looking for matching "
# define ERROR_NL "minishell: syntax error near unexpected token `newline`"
# define ERROR_HD "minishell: warning: here-document delimited by end-of-file"

int		ft_check_grammar(t_token **tokens);
int		ft_check_redir(t_token **tokens, size_t i);
int		ft_check_quotes(t_token *token, char *quote);
int		ft_check_here_doc(t_token **tokens, size_t i);
int		ft_in_quotes(char *str, size_t *i, char *quote);

char	*ft_search_in_directory(char *cmd);
void	ft_print_error(char *file, char *msg);
char	*ft_search_path(t_list **env, char *cmd);

void	ft_get_cmd(char **command);
void	ft_command_not_found(char *arg);
size_t	ft_count_exec_blocks(t_token **tokens);
char	*ft_check_path(char **paths, char *cmd);
void	ft_free_command_norme(t_data *data, char *arg);

int		ft_isop(int type);
int		ft_isvalidtype(int type);
int		ft_isredir(t_token *token);
size_t	ft_tab_size(t_token **tokens);
int		ft_check_op(t_token **tokens, size_t i);

int		ft_wait_all(t_data *data);
void	ft_close(int *fd1, int *fd2);
int		ft_get_return_val(int status);
int		ft_glhf(char *args, char *args2);
void	ft_exec_builtin_pipe(t_data *data, t_token **args);

#endif
