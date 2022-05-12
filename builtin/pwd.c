/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:00:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/10 11:51:56 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	buf[PATH_MAX];
	char	*cwd;
	char	*temp;

	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		return (0);
	temp = ft_strjoin(cwd, "\n");
	ft_putstr(temp);
	free(temp);
	return (1);
}

void	ft_update_env(t_list **env, char *name, char *value)
{
	t_list	*temp;
	char	*str;
	int		str_lenght;

	if (!env || !(*env))
		return ;
	temp = *env;
	str = ft_strjoin(name, value);
	str_lenght = ft_strlen(name);
	while (temp && ft_strncmp(name, temp->content, str_lenght))
		temp = temp->next;
	if (!temp)
		return ;
	free(temp->content);
	temp->content = str;
}
