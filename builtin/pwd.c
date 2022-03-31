/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:00:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/31 09:52:00 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	char	*cwd;

	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		return (0);
	ft_putstr(cwd);
	ft_putchar('\n');
	return (1);
}

void	ft_update_env(t_list **env, char *name, char *value)
{
	t_list	*temp;
	char	*str;
	int		str_lenght;

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
