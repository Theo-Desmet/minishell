/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:41:13 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/21 13:55:43 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

pid_t	*ft_update_childs(t_data *data, size_t n)
{
	pid_t	*res;

	if (data->childs)
		free(data->childs);
	res = ft_calloc(n + 1, sizeof(pid_t));
	if (!res)
		return (NULL); //PROTECT
	return (res);	
}

int	**ft_update_pipes(t_data *data, size_t n)
{
	int		**pipes;
	ssize_t	i;

	if (data->pipes)
		free(ft_free_tab((void **)data->pipes));
	pipes = ft_calloc(n + 1, sizeof(int *));
	if (!pipes)
		return (NULL); //PROTECT
	i = -1;
	while (++i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (ft_free_tab((void **)pipes), NULL); // PROTECT
		pipe(pipes[i]);
	}
	return (pipes);
}

void	ft_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	ft_exec_builtin_pipe(t_data *data, t_token **args)
{
	char	**cmd;
	char    *command;

	command = ft_join_word(args);
	cmd = ft_lexer(command);
	ft_get_cmd(cmd);
	if (!ft_strcmp("cd", cmd[0]))
			g_global->rtn_val = ft_cd(data, cmd);
	else if (!ft_strcmp("pwd", cmd[0]))
			g_global->rtn_val = ft_pwd(data);
	else if (!ft_strcmp("env", cmd[0]))
			g_global->rtn_val = ft_env(data->env);
	else if (!ft_strcmp("echo", cmd[0]))
			g_global->rtn_val = ft_echo(cmd);
	else if (!ft_strcmp("export", cmd[0]))
			g_global->rtn_val = ft_export(data->env, cmd);
	else if (!ft_strcmp("unset", cmd[0]))
			g_global->rtn_val = ft_unset(data->env, cmd);
	else if (!ft_strcmp("exit", cmd[0]))
			;
	exit(g_global->rtn_val);
}

void	ft_exec_first(t_data *data, t_token **args)
{
	char	*cmd;
	char	*here_doc;
	
	here_doc = ft_check_last_heredoc(data, args);
	data->childs[0] = fork();
	g_global->pid = data->childs[0];
	if (data->childs[0] < 0)
	{
		//ft_free_data(data);
		return ;
	}
	if (!data->childs[0])
	{
		close(data->pipes[0][0]);
		ft_redirection(data, args, 0);
		if (here_doc)
		{
			ft_rd_in(data, here_doc, 0);
			free(here_doc);
		}
		cmd = ft_join_word(args);
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->pipes[0][1], STDOUT_FILENO);
		ft_close(data->fd_in, data->pipes[0][1]);
		if (ft_check_builtin(data, args))
			ft_exec_builtin_pipe(data, args);
		else
			ft_exec(data->env, cmd);
		//ft_free_data(data);
	}
	else
		ft_close(data->fd_in, data->pipes[0][1]);
}

void	ft_exec_mid(t_data *data, t_token **args, int i)
{
	char	*cmd;
	char	*here_doc;
	
	here_doc = ft_check_last_heredoc(data, args);
	data->childs[i] = fork();
	g_global->pid = data->childs[i];
	if (data->childs[i] < 0)
	{
		//ft_free_data(data);
		return ;
	}
	if (!data->childs[i])
	{
		close(data->pipes[i][0]);
		ft_redirection(data, args, i); 
		if (here_doc)
		{
			ft_rd_in(data, here_doc, i);
			free(here_doc);
		}
		cmd = ft_join_word(args);
		dup2(data->pipes[i - 1][0], STDIN_FILENO);
		dup2(data->pipes[i][1], STDOUT_FILENO);
		ft_close(data->pipes[i - 1][0], data->pipes[i][1]);
		if (ft_check_builtin(data, args))
			ft_exec_builtin_pipe(data, args);
		else
			ft_exec(data->env, cmd);
		//ft_free_data(data);
	}
	else
		ft_close(data->pipes[i - 1][0], data->pipes[i][1]);
}

void	ft_exec_last(t_data *data, t_token **args, int last)
{
	char	*cmd;
	char	*here_doc;

	here_doc = ft_check_last_heredoc(data, args);
	data->childs[last] = fork();
	g_global->pid = data->childs[last];
	if (data->childs[last] < 0)
		return ;
	if (!data->childs[last])
	{
		close(data->pipes[last - 1][1]);
		ft_redirection(data, args, last);
		if (here_doc)
		{
			ft_rd_in(data, here_doc, last);
			free(here_doc);
		}
		cmd = ft_join_word(args);
		dup2(data->fd_out, STDOUT_FILENO);
		dup2(data->pipes[last - 1][0], STDIN_FILENO);
		ft_close(data->pipes[last - 1][0], data->fd_out);
		if (ft_check_builtin(data, args))
			ft_exec_builtin_pipe(data, args);
		else
			ft_exec(data->env, cmd);
	}
	else
		ft_close(data->fd_out, data->pipes[last - 1][0]);
}

int		ft_is_last_pipe(t_token **args)
{
	size_t	i;

	i = 1;
	while (args[i] && args[i]->type != D_AND && args[i]->type != D_PIPE)
	{
		if (args[i] && args[i]->type == PIPE)
			return (0);
		i++;
	}
	return (1);

}

size_t	ft_go_to_next_pipe(t_token **args)
{
	size_t	i;

	i = 0;
	while (args[i] && args[i]->type != PIPE	&& args[i]->type != D_PIPE && args[i]->type != D_AND)
		i++;
	return (i);
}

void	ft_exec_pipeline(t_data *data, t_token **args, size_t pipes)
{
	size_t	i;
	size_t	p;
	i = 0;
	p = 1;
	ft_exec_first(data, args);
	while (--pipes)
	{
		i += ft_go_to_next_pipe(&args[i]) + 1;
		ft_exec_mid(data, &args[i], p++);
	}
	i += ft_go_to_next_pipe(&args[i]) + 1;
	ft_exec_last(data, &args[i], p);
}

int	ft_get_return_val(int status)
{
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return(128 + WTERMSIG(status));
	return (0);
}

int	ft_wait_all(t_data *data)
{
	int		status;
	int		res;
	ssize_t	i;

	res = 0;
	i = -1;
	status = 0;
	while (data->childs[++i])
	{
		waitpid(data->childs[i], &status, 0);
		res = ft_get_return_val(status);
	}
	return (res);
}

int     ft_glhf(char *args, char *args2)
{
		int     bastien;

		bastien = 0;
		while (args[bastien] && args2[bastien])
		{
				if (args[bastien] != args2[bastien])
						return (0);
				bastien++;
		}
		if (!args2[bastien] || args2[bastien] == ' ')
				return (1);
		return (0);
}

int     ft_check_builtin(t_data *data, t_token **args)
{
		int i;
		char *cmd;

		i = 0;
		while (args && args[i]->type != WORD)
				i++;
		cmd = args[i]->val;
		if (ft_glhf("cd", cmd)
			|| ft_glhf("pwd", cmd)
			|| ft_glhf("env", cmd)
			|| ft_glhf("echo", cmd)
			|| ft_glhf("export", cmd)
			|| ft_glhf("unset", cmd)
			|| ft_glhf("exit", cmd))
		{
				return (1);
		}
		return (0);
}

int     ft_exec_builtin(t_data *data, t_token **args)
{
		char    *command;
		char    **cmd;

		ft_redirection(data, args, 0);
		ft_check_last_heredoc(data, args);
		command = ft_join_word(args);
		cmd = ft_lexer(command);
		ft_get_cmd(cmd);
		if (!ft_strcmp("cd", cmd[0]))
				g_global->rtn_val = ft_cd(data, cmd);
		else if (!ft_strcmp("pwd", cmd[0]))
				g_global->rtn_val = ft_pwd(data);
		else if (!ft_strcmp("env", cmd[0]))
				g_global->rtn_val = ft_env(data->env);
		else if (!ft_strcmp("echo", cmd[0]))
				g_global->rtn_val = ft_echo(cmd);
		else if (!ft_strcmp("export", cmd[0]))
				g_global->rtn_val = ft_export(data->env, cmd);
		else if (!ft_strcmp("unset", cmd[0]))
				g_global->rtn_val = ft_unset(data->env, cmd);
		else if (!ft_strcmp("exit", cmd[0]))
				;
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
	f = fork();
	if (!f)
	{
		ft_redirection(data, args, 0);
		here_doc = ft_check_last_heredoc(data, args);
		if (here_doc)
			ft_rd_in(data, here_doc, 0);
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		cmd = ft_join_word(args);
		ft_exec(data->env, cmd);
	}
	else
	{
		waitpid(f, &status, 0);
		g_global->rtn_val = ft_get_return_val(status);
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
				g_global->rtn_val = ft_wait_all(data);
			}
			pipeline += offset;
			if (!*pipeline || (((*pipeline)->type == D_AND && g_global->rtn_val != 0)
				|| ((*pipeline)->type == D_PIPE && g_global->rtn_val == 0)))
				break;
			else
				pipeline++;
		}
	}
	data->act_heredoc = -1;
	data->nb_heredoc = 0;
}

size_t	ft_count_pipes(t_token	**tokens, size_t *offset)
{
	ssize_t	i;
	size_t	count;

	i = -1;
	count = 0;
	if (!tokens || !*tokens)
		return (0);
	while (tokens[++i] && tokens[i]->type != D_PIPE && tokens[i]->type != D_AND)
		if (tokens[i]->type == PIPE)
			count++;
	if (offset)
		*offset = i;
	return (count);
}

