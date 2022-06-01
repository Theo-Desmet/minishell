/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:47:01 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/01 18:52:08 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_child_cmd(t_data *data, t_token **args)
{
	char	*here_doc;
	char	*cmd;

	ft_redirection(data, args, 0);
	here_doc = ft_check_last_heredoc(data, args);
	if (here_doc)
	{
		ft_rd_in(data, here_doc, 0);
		unlink(here_doc);
	}
	dup2(data->fd_in, STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	cmd = ft_join_word(args);
	ft_exec(data, data->env, cmd);
}

void	ft_cmd(t_data *data, t_token **args)
{
	int		status;

	if (ft_check_builtin(args))
	{
		ft_exec_builtin(data, args);
		return ;
	}
	g_global.pid = fork();
	if (!g_global.pid)
		ft_child_cmd(data, args);
	else
	{
		waitpid(g_global.pid, &status, WUNTRACED);
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
				|| tokens[i]->type == D_PIPE || tokens[i]->type == D_AND))
		{
			res++;
			i++;
		}
	}
	return (res);
}

void	ft_prepare_pipeline(t_data *data, size_t *offset, t_token **pipeline)
{
	size_t	pipes;

	data->fd_in = dup(STDIN_FILENO);
	data->fd_out = dup(STDOUT_FILENO);
	pipes = ft_count_pipes(pipeline, offset);
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
}

void	ft_pipeline(t_data *data, t_token **tokens)
{
	t_token	**pipeline;
	size_t	offset;

	pipeline = tokens - 1;
	offset = 0;
	ft_find_heredoc(data, tokens);
	if (ft_count_exec_blocks(tokens) == 1)
		ft_cmd(data, tokens);
	else
	{
		while (*(++pipeline))
		{
			ft_prepare_pipeline(data, &offset, pipeline);
			pipeline += offset;
			if (!*pipeline || (((*pipeline)->type == D_AND
						&& g_global.rtn_val != 0)
					|| ((*pipeline)->type == D_PIPE
						&& g_global.rtn_val == 0)))
				break ;
		}
	}
	data->act_heredoc = -1;
	data->nb_heredoc = 0;
	data->nb_pipes = 0;
}
