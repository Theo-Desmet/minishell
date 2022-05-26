/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:47:01 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 16:57:47 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_exec_builtin_pipe(t_data *data, t_token **args)
{
	char	**cmd;
	char    *command;

	command = ft_join_word(args);
	cmd = ft_lexer(command);
	ft_get_cmd(cmd);
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
			ft_exit(cmd);
	ft_free_tab((void **)cmd);
	free(command);
	ft_free_data(data);
	exit(g_global.rtn_val);
}

int	ft_exec_builtin(t_data *data, t_token **args)
{
	char	*command;
	char	**cmd;
	int		in;
	int		out;
	
	in = dup(data->fd_in);
	out	= dup(data->fd_out);
	ft_redirection(data, args, 0);
	ft_check_last_heredoc(data, args);
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	command = ft_join_word(args);
	cmd = ft_lexer(command);
	ft_get_cmd(cmd);
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
			ft_exit(cmd);
	ft_free_tab((void **)cmd);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	free(command);
}

void	ft_cmd(t_data *data, t_token **args)
{
	pid_t	f; 
	char	*cmd;
	int		status;
	char	*here_doc;

	if (ft_check_builtin(data, args))
	{
		ft_exec_builtin(data, args);
		return ;
	}
	g_global.pid = fork();
	if (!g_global.pid)
	{
		ft_redirection(data, args, 0);
		here_doc = ft_check_last_heredoc(data, args);
		if (here_doc)
			ft_rd_in(data, here_doc, 0);
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		cmd = ft_join_word(args);
		ft_exec(data, data->env, cmd);
	}
	else
	{
		waitpid(g_global.pid , &status, 0);
		g_global.rtn_val = ft_get_return_val(status);
	}
}

size_t	ft_count_exec_blocks(t_token **tokens)
{
	size_t	res;
	size_t	i;

	res = 1;
	i = 0;
	while (tokens[i])
	{
		while (tokens[i] && tokens[i]->type != PIPE
			&& tokens[i]->type != D_PIPE && tokens[i]->type != D_AND)
			i++;
		if (tokens[i] && (tokens[i]->type == PIPE
			|| tokens[i]->type == D_PIPE || tokens[i]->type == D_AND) )
		{
			res++;
			i++;
		}
	}
	return (res);
}

void	ft_pipeline(t_data *data, t_token **tokens)
{
	t_token	**pipeline;
	size_t	offset;
	size_t	pipes;

	pipeline = tokens;
	offset = 0;
	ft_find_heredoc(data, tokens);
	if (ft_count_exec_blocks(tokens) == 1)
		ft_cmd(data, tokens);
	else
	{
		while (*pipeline)
		{
			data->fd_in = dup(STDIN_FILENO);
			data->fd_out = dup(STDOUT_FILENO);
			pipes = ft_count_pipes(pipeline, &offset);
			data->nb_pipes = pipes;
			if (pipes == 0)
				ft_cmd(data, pipeline);
			else
			{
				data->childs = ft_update_childs(data, pipes + 1);
				data->pipes = ft_update_pipes(data, pipes);
				ft_exec_pipeline(data, pipeline, pipes);
				g_global.rtn_val = ft_wait_all(data);
			}
			pipeline += offset;
			if (!*pipeline || (((*pipeline)->type == D_AND && g_global.rtn_val != 0)
				|| ((*pipeline)->type == D_PIPE && g_global.rtn_val == 0)))
				break;
			else
				pipeline++;
		}
	}
	data->act_heredoc = -1;
	data->nb_heredoc = 0;
	data->nb_pipes = 0;
}
