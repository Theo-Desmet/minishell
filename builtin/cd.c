/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:51:41 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/23 13:53:57 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_list **env, char *str)
{
	t_list	*temp;
	size_t	i;
	int		lenght;

	i = 0;
	if (!env || !(*env))
		return (NULL);
	temp = *env;
	lenght = ft_strlen(str);
	while (temp && ft_strncmp(str, temp->content, lenght))
		temp = temp->next;
	if (!temp)
		return (NULL);
	return (&((char *)temp->content)[lenght + 1]);
}

int	ft_cd_home(t_data *data, char **str)
{
	char	*home;
	char	*cwd;

	home = ft_getenv(data->env, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (!chdir(home))
	{
		cwd = NULL;
		cwd = getcwd(cwd, 0);
		if (!cwd)
			return (0);
		ft_update_env(data, data->env, "OLDPWD=", ft_getenv(data->env, "PWD"));
		ft_update_env(data, data->env, "PWD=", cwd);
		free(cwd);
		return (0);
	}
	return (ft_cd_error(str));
}

int	ft_cd_error(char **str)
{
	char	*msg;

	msg = NULL;
	if (str[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	msg = ft_strjoin("minishell: cd: ", str[1]);
	perror(msg);
	free(msg);
	return (1);
}

int	ft_cd(t_data *data, char **str)
{
	DIR		*dir;
	char	*cwd;

	if (!str[1] || !ft_strcmp(str[1], "~"))
		return (ft_cd_home(data, str));
	if (str[2])
		return (ft_cd_error(str));
	dir = opendir(str[1]);
	if (!dir)
		return (ft_cd_error(str));
	closedir(dir);
	if (chdir(str[1]))
		return (ft_cd_error(str));
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
	{
		free(cwd);
		return (1);
	}
	ft_update_env(data, data->env, "OLDPWD=", ft_getenv(data->env, "PWD"));
	ft_update_env(data, data->env, "PWD=", cwd);
	free(cwd);
	return (0);
}
