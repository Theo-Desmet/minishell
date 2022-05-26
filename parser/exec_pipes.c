/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:48:47 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 16:49:57 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_exec_first(t_data *data, t_token **args)
{
	char	*cmd;
	char	*here_doc;
	
	here_doc = ft_check_last_heredoc(data, args);
	data->childs[0] = fork();
	g_global.pid = data->childs[0];
	if (data->childs[0] < 0)
	{
		ft_free_data(data);
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
		{
			free(cmd);
			ft_exec_builtin_pipe(data, args);
		}
		else
			ft_exec(data, data->env, cmd);
		ft_free_data(data);
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
	g_global.pid = data->childs[i];
	if (data->childs[i] < 0)
	{
		ft_free_data(data);
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
			ft_exec(data, data->env, cmd);
		ft_free_data(data);
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
	g_global.pid = data->childs[last];
	if (data->childs[last] < 0)
	{
		ft_free_data(data);
		return ;
	}
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
			ft_exec(data, data->env, cmd);
		ft_free_data(data);
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