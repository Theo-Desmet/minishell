/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:08:35 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/05 11:58:15 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_print_error(char *file, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
}

char	*ft_search_in_directory(char *cmd)
{
	int	dir;

	dir = open(cmd, __O_DIRECTORY);
	if (!access(cmd, X_OK | F_OK) && dir == -1)
		return (cmd);
	if (dir == -1 && access(cmd, F_OK))
		ft_print_error(cmd, "No such file or directory\n");
	else if (dir > 0)
		ft_print_error(cmd, "is directory\n");
	else
		ft_print_error(cmd, "Permission denied\n");
	if (dir > 0)
		close(dir);
	return (NULL);
}

char	*ft_search_path(t_list **env, char *cmd)
{
	t_list	*temp;
	char	**paths;
	char	*command;

	if (ft_strchr(cmd, '/'))
		return (ft_search_in_directory(cmd));
	if (!env || !*env)
		return (ft_print_error(cmd, "command not found\n"), NULL);
	temp = *env;
	while (temp && temp->next && ft_strncmp("PATH=", temp->content, 5))
		temp = temp->next;
	if (!temp->next || ft_strncmp("PATH=", temp->content, 5))
		return (ft_print_error(cmd, "command not found\n"), NULL);
	paths = ft_split(temp->content + 5, ':');
	command = ft_check_path(paths, cmd);
	ft_free_tab((void **)paths);
	if (!command)
		return (ft_print_error(cmd, "command not found\n"), NULL);
	return (command);
}
