/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:41:13 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 16:51:47 by bbordere         ###   ########.fr       */
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
		return (NULL);
	return (res);	
}

int	**ft_update_pipes(t_data *data, size_t n)
{
	int		**pipes;
	ssize_t	i;

	if (data->pipes)
		ft_free_tab((void **)data->pipes);
	pipes = ft_calloc(n + 1, sizeof(int *));
	if (!pipes)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (ft_free_tab((void **)pipes), NULL);
		pipe(pipes[i]);
	}
	return (pipes);
}

void	ft_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
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
	if (g_global.rtn_val == 130 && g_global.in_exec == 1)
		return (130);
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
		int     i;

		i = 0;
		while (args[i] && args2[i])
		{
				if (args[i] != args2[i])
						return (0);
				i++;
		}
		if (!args2[i] || args2[i] == ' ')
				return (1);
		return (0);
}

int     ft_check_builtin(t_data *data, t_token **args)
{
		int i;
		char *cmd;

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
		{
				return (1);
		}
		return (0);
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

