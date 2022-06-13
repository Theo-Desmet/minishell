/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:51:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/13 15:59:02 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin(t_data *data, char **cmd, char *command)
{
	if (!ft_strcmp("cd", cmd[0]))
		g_global.rtn_val = ft_cd(data, cmd);
	else if (!ft_strcmp("pwd", cmd[0]))
		g_global.rtn_val = ft_pwd(data);
	else if (!ft_strcmp("env", cmd[0]))
		g_global.rtn_val = ft_env(data->env);
	else if (!ft_strcmp("echo", cmd[0]))
		g_global.rtn_val = ft_echo(cmd);
	else if (!ft_strcmp("export", cmd[0]))
		g_global.rtn_val = ft_export(data->env, cmd);
	else if (!ft_strcmp("unset", cmd[0]))
		g_global.rtn_val = ft_unset(data->env, cmd);
	else if (!ft_strcmp("exit", cmd[0]))
		ft_exit(data, cmd, command);
}

int	ft_open_err_builtin(t_data *data, int in, int out)
{
	if (data->fd_in == -1 || data->fd_out == -1)
	{
		ft_close(&in, &out);
		return (1);
	}
	return (0);
}

void	ft_exec_builtin(t_data *data, t_token **args)
{
	char	*command;
	char	**cmd;
	int		fd[2];

	fd[0] = dup(data->fd_in);
	fd[1] = dup(data->fd_out);
	ft_redirection(data, args, 0);
	command = ft_check_last_heredoc(data, args);
	if (command)
		ft_redir_here_doc(data, command, 0);
	if (ft_open_err_builtin(data, fd[0], fd[1]))
		return ;
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	command = ft_join_word(args);
	cmd = ft_lexer(command);
	ft_get_cmd(cmd);
	if (!ft_strcmp("exit", cmd[0]))
		ft_close(&fd[0], &fd[1]);
	ft_builtin(data, cmd, command);
	ft_free_tab((void **)cmd);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	ft_close(&fd[0], &fd[1]);
	free(command);
}

void	ft_child(t_data *data, t_token **args, int *in, int *out)
{
	char	*cmd;

	cmd = ft_join_word(args);
	dup2(*in, STDIN_FILENO);
	dup2(*out, STDOUT_FILENO);
	ft_close(in, out);
	ft_close_all(data);
	if (ft_check_builtin(args))
	{
		free(cmd);
		ft_exec_builtin_pipe(data, args);
	}
	else
		ft_exec(data, data->env, cmd);
	ft_free_data(data);
}

int	ft_check_builtin(t_token **args)
{
	int		i;
	char	*cmd;

	i = 0;
	while (args[i] && args[i]->type != WORD)
			i++;
	if (!args[i])
		return (0);
	cmd = args[i]->val;
	if (ft_glhf("cd", cmd)
		|| ft_glhf("pwd", cmd)
		|| ft_glhf("env", cmd)
		|| ft_glhf("echo", cmd)
		|| ft_glhf("export", cmd)
		|| ft_glhf("unset", cmd)
		|| ft_glhf("exit", cmd))
		return (1);
	return (0);
}
