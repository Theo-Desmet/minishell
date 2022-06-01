/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:51:59 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/01 18:54:16 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	ft_exec_builtin_pipe(t_data *data, t_token **args)
{
	char	**cmd;
	char	*command;

	command = ft_join_word(args);
	cmd = ft_lexer(command);
	ft_get_cmd(cmd);
	ft_builtin(data, cmd, command);
	ft_free_tab((void **)cmd);
	free(command);
	ft_free_data(data);
	exit(g_global.rtn_val);
}

void	ft_exec_builtin(t_data *data, t_token **args)
{
	char	*command;
	char	**cmd;
	int		in;
	int		out;

	in = dup(data->fd_in);
	out = dup(data->fd_out);
	ft_redirection(data, args, 0);
	command = ft_check_last_heredoc(data, args);
	if (command)
	{
		ft_rd_in(data, command, 0);
		unlink(command);
		free(command);
	}
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	command = ft_join_word(args);
	cmd = ft_lexer(command);
	ft_get_cmd(cmd);
	ft_builtin(data, cmd, command);
	ft_free_tab((void **)cmd);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	free(command);
}

void	ft_child(t_data *data, t_token **args, int in, int out)
{
	char	*cmd;

	cmd = ft_join_word(args);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	ft_close(in, out);
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
