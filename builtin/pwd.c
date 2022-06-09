/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:00:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/09 10:20:54 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	char	*cwd;
	char	*temp;

	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		cwd = data->pwd;
	temp = ft_strjoin(cwd, "\n");
	ft_printf("%s", temp);
	free(temp);
	return (0);
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

void	ft_update_env_norme(t_list **env, char *name, char *str)
{
	int		str_lenght;
	t_list	*temp;

	temp = *env;
	str_lenght = ft_strlen(name);
	while (temp && ft_strncmp(name, temp->content, str_lenght))
		temp = temp->next;
	if (!temp)
	{
		free(str);
		return ;
	}
	free(temp->content);
	temp->content = str;
	return ;
}

void	ft_update_env(t_data *data, t_list **env, char *name, char *value)
{
	char	*str;
	char	*mem;

	if (!value)
		return ;
	mem = ft_strdup(value);
	if (!mem)
		return ;
	free(data->pwd);
	data->pwd = mem;
	if (!*env)
		return ;
	str = ft_strjoin(name, value);
	if (!str)
	{
		free(mem);
		return ;
	}
	ft_update_env_norme(env, name, str);
}
