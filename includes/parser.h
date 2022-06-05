/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:20:53 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/05 12:01:27 by bbordere         ###   ########.fr       */
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
int		ft_check_builtin(t_token **args);
void	ft_get_cmd(char **command);
void	ft_exec_builtin(t_data *data, t_token **args);
void	ft_restore_fd(t_data *data);
size_t	ft_count_pipes(t_token	**tokens, size_t *offset);
void	ft_pipeline(t_data *data, t_token **tokens);
char	**ft_lst_to_tab(t_list **lst);
char	*ft_check_last_heredoc(t_data *data, t_token **args);
void	ft_redirection(t_data *data, t_token **args, int index);
void	ft_rd_in(t_data *data, char *arg, int i);
char	*ft_join_word(t_token **args);
void	ft_exec(t_data *data, t_list **env, char *arg);
void	ft_find_heredoc(t_data *data, t_token **args);
void	ft_lstdel_all(t_list **lst);
int		ft_cd(t_data *data, char **str);
int		ft_echo(char **args);
int		ft_env(t_list **env);
int		ft_export(t_list **env, char **arg);
int		ft_pwd(t_data *data);
int		ft_unset(t_list **env, char **arg);
void	ft_exit(t_data *data, char **args, char *command);
void	ft_free_lexer(t_data *data);
void	ft_free_data(t_data *data);
void	ft_rd_in(t_data *data, char *arg, int i);
void	ft_rd_out(t_data *data, char *arg, int i);
void	ft_rd_append(t_data *data, char *arg, int i);
void	ft_here_doc(char *limiter, char *line, int fd, int len);
char	*ft_check_path(char **paths, char *cmd);
char	*ft_search_path(t_list **env, char *cmd);
void	ft_command_not_found(char *arg);
void	ft_free_command_norme(t_data *data, char *arg);
void	ft_get_cmd(char **command);
int		ft_isredir(t_token *token);
void	ft_get_doc(char *limiter, int nb_heredoc);
void	ft_cmd(t_data *data, t_token **args);
size_t	ft_count_exec_blocks(t_token **tokens);
void	ft_pipeline(t_data *data, t_token **tokens);
void	ft_exec_builtin_pipe(t_data *data, t_token **args);
void	ft_exec_first(t_data *data, t_token **args);
void	ft_exec_mid(t_data *data, t_token **args, int i);
void	ft_exec_last(t_data *data, t_token **args, int last);
int		ft_is_last_pipe(t_token **args);
size_t	ft_go_to_next_pipe(t_token **args);
pid_t	*ft_update_childs(t_data *data, size_t n);
int		**ft_update_pipes(t_data *data, size_t n);
void	ft_close(int fd1, int fd2);
void	ft_exec_pipeline(t_data *data, t_token **args, size_t pipes);
int		ft_get_return_val(int status);
int		ft_wait_all(t_data *data);
void	*ft_free_tokens(t_token **tokens);
void	ft_free_lexer(t_data *data);
void	ft_free_data(t_data *data);
void	ft_lstdel_all(t_list **lst);
int		ft_sig_init(void);
void	ft_builtin(t_data *data, char **cmd, char *command);
void	ft_exec_builtin_pipe(t_data *data, t_token **args);
void	ft_exec_builtin(t_data *data, t_token **args);
void	ft_child(t_data *data, t_token **args, int in, int out);
int		ft_glhf(char *args, char *args2);
void	ft_close(int fd1, int fd2);
void	ft_close_all(t_data *data);
size_t	ft_count_exec_blocks(t_token **tokens);
void	ft_redir_here_doc(t_data *data, char *command, int i);

#endif
