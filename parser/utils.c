/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:31:09 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/29 12:32:30 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_check_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

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

char	*ft_search_path(t_list **env, char *cmd)
{
	char	**paths;
	char	*command;
	t_list	*temp;

	if (!access(cmd, X_OK | F_OK) && (!ft_strncmp(cmd, "./", 2)
			|| !ft_strncmp(cmd, "/", 1)))
		return (cmd);
	if (!env || !(*env))
		return (NULL);
	temp = *env;
	while (temp && temp->next && ft_strncmp("PATH=", temp->content, 5))
		temp = temp->next;
	if (!temp->next || ft_strncmp("PATH=", temp->content, 5))
		return (NULL);
	paths = ft_split(temp->content + 5, ':');
	command = ft_check_path(paths, cmd);
	ft_free_tab((void **)paths);
	if (!command)
		return (NULL);
	return (command);
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
	ssize_t	j;
	size_t	len;

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
