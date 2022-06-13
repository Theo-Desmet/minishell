/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:32:16 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/13 17:19:41 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	ft_get_doc(char *limiter, int nb_heredoc);
void	ft_here_doc(char *limiter, char *line, int fd, int len);

void	ft_unlink_file(t_data *data);
void	ft_redir_here_doc(t_data *data, char *command, int i);
char	*ft_check_last_heredoc(t_data *data, t_token **args);
void	ft_unlink_wrong_heredoc(t_data *data, t_token **args);
int		*ft_check_last_heredoc2(t_data *data, t_token **args, int cnt[2]);

int		ft_check_builtin(t_token **args);
void	ft_exec_builtin(t_data *data, t_token **args);
int		ft_open_err_builtin(t_data *data, int in, int out);
void	ft_builtin(t_data *data, char **cmd, char *command);
void	ft_child(t_data *data, t_token **args, int *in, int *out);

void	ft_cmd(t_data *data, t_token **args);
void	ft_child_cmd(t_data *data, t_token **args);
void	ft_pipeline(t_data *data, t_token **tokens);
void	ft_pipeline_routine(t_data *data, t_token ***pipeline);
void	ft_prepare_pipeline(t_data *data, size_t *offset, t_token **pipeline);

int		ft_is_last_pipe(t_token **args);
size_t	ft_go_to_next_pipe(t_token **args);
void	ft_exec_first(t_data *data, t_token **args);
void	ft_exec_mid(t_data *data, t_token **args, int i);
void	ft_exec_last(t_data *data, t_token **args, int last);

int		ft_wd_file(t_data *data, char **var);
int		ft_rd_in(t_data *data, char **arg, int i);
int		ft_rd_out(t_data *data, char **arg, int i);
int		ft_rd_append(t_data *data, char **arg, int i);
int		ft_check_files(t_data *data, char **arg, int mode);

pid_t	*ft_update_childs(t_data *data, size_t n);
int		**ft_update_pipes(t_data *data, size_t n);
size_t	ft_count_pipes(t_token **tokens, size_t *offset);
void	ft_exec_pipeline(t_data *data, t_token **args, size_t pipes);

char	*ft_join_word(t_token **args);
void	ft_find_heredoc(t_data *data, t_token **args);
void	ft_exec(t_data *data, t_list **env, char *arg);
void	ft_redirection(t_data *data, t_token **args, int index);
void	ft_exit_exec(char **command, t_data *data, char **tab_env);

#endif
