/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:00:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/15 10:28:29 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	char	*cwd;
	char	*temp;

	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		cwd = data->pwd;
	temp = ft_strjoin(cwd, "\n");
	ft_putstr(temp, NULL);
	free(temp);
	return (1);
}

char	*ft_pwd_str(void)
{
	char	buf[PATH_MAX];
	char	*cwd;

	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		return (NULL);
	return ((char *)cwd);
}

void	ft_update_env(t_data *data, t_list **env, char *name, char *value)
{
	t_list	*temp;
	char	*str;
	int		str_lenght;

	if (!env || !(*env) || !value)
		return ;
	temp = *env;
	value = strdup(value);
	data->pwd = value;
	str = ft_strjoin(name, value);
	str_lenght = ft_strlen(name);
	while (temp && ft_strncmp(name, temp->content, str_lenght))
		temp = temp->next;
	if (!temp)
		return ;
	free(temp->content);
	temp->content = str;
}
