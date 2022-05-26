/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:39:16 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/26 19:39:16 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_exit_exec(char **command, t_data *data)
{
	ft_command_not_found(command[0]);
	ft_free_tab((void **)command);
	ft_free_data(data);
	exit(127);
}

void	ft_exec(t_data *data, t_list **env, char *arg)
{
	char	**command;
	char	*path;

	command = ft_lexer(arg);
	ft_get_cmd(command);
	if (!command)
		ft_free_command_norme(data, arg);
	if (!*command)
	{
		ft_free_data(data);
		ft_free_tab((void **)command);
		exit(EXIT_SUCCESS);
	}
	free(arg);
	path = ft_search_path(env, command[0]);
	if (!path)
		ft_exit_exec(command, data);
	if (execve(path, command, ft_lst_to_tab(env)))
		ft_exit_exec(command, data);
	ft_free_tab((void **)command);
}

void	ft_find_heredoc(t_data *data, t_token **args)
{
	size_t	i;
	size_t	nb_heredoc;

	i = 0;
	nb_heredoc = 0;
	while (args[i])
	{
		if (args[i]->type == R_HERE_DOC)
		{
			ft_get_doc(args[++i]->val, nb_heredoc);
			nb_heredoc++;
		}
		i++;
	}
	data->nb_heredoc = nb_heredoc;
}

void	ft_redirection(t_data *data, t_token **args, int index)
{
	int	i;

	i = 0;
	while (args[i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == R_IN)
			ft_rd_in(data, args[++i]->val, index);
		if (args[i]->type == R_OUT)
			ft_rd_out(data, args[++i]->val, index);
		if (args[i]->type == R_APPEND)
			ft_rd_append(data, args[++i]->val, index);
		i++;
	}
}

char	*ft_join_word(t_token **args)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = NULL;
	while (args[i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == WORD)
			cmd = ft_strjoin1(ft_strjoin1(cmd, args[i]->val), " ");
		i++;
	}
	if (!cmd || !(*cmd))
		return (NULL);
	if (cmd[ft_strlen(cmd) - 1] == ' ')
		cmd[ft_strlen(cmd) - 1] = '\0';
	return (cmd);
}
