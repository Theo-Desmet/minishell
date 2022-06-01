/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:41:13 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/01 18:56:40 by bbordere         ###   ########.fr       */
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
	while (++i < (ssize_t)n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (ft_free_tab((void **)pipes), NULL);
		pipe(pipes[i]);
	}
	return (pipes);
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
