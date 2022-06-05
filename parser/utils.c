/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:31:09 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/05 11:33:17 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_check_path(char **paths, char *cmd)
{
	char		*tmp;
	char		*command;
	size_t		i;

	i = 0;
	while (cmd[i] && (cmd[i] == '/' || cmd[i] == '.'))
		i++;
	if (!cmd[i])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	ft_command_not_found(char *arg)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_free_command_norme(t_data *data, char *arg)
{
	ft_command_not_found(arg);
	free(arg);
	ft_free_data(data);
	exit(EXIT_FAILURE);
}

void	ft_get_cmd(char **command)
{
	ssize_t	i;

	i = -1;
	if (!command || !*command)
		return ;
	while (command[++i])
	{
		if (ft_issep(command[i][0]))
		{
			ft_memmove(command[i], &command[i][1], ft_strlen(command[i]));
			command[i][ft_strlen(command[i]) - 1] = '\0';
		}
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
