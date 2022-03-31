/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:51:41 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/31 09:52:22 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd_home(t_data *data, char *str)
{
	char	*home;
	char	*cwd;

	home = ft_getenv(data->env, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set \n", 2);
		return (0);
	}
	if (!chdir(home))
	{
		cwd = NULL;
		cwd = getcwd(cwd, 0);
		if (!cwd)
			return (0);
		ft_update_env(data->env, "OLDPWD=", ft_getenv(data->env, "PWD"));
		ft_update_env(data->env, "PWD=", cwd);
		free(cwd);
		return (1);
	}
	return (ft_cd_error(home));
}

int	ft_cd_error(char *str)
{
	perror("minishell: cd");
	return (0);
}

char	*ft_getenv(t_list **env, char *str)
{
	t_list	*temp;
	size_t	i;
	int		lenght;

	i = 0;
	temp = *env;
	lenght = ft_strlen(str);
	while (temp && ft_strncmp(str, temp->content, lenght))
		temp = temp->next;
	if (!temp)
		return (NULL);
	return (&(temp->content)[lenght + 1]);
}

int	ft_cd(t_data *data, char **str)
{
	DIR		*dir;
	char	*cwd;

	if (!(str && *str))
		return (ft_cd_home(data, *str));
	if (str[1])
		return (ft_cd_error(*str));
	dir = opendir(str[0]);
	if (!dir)
		return (ft_cd_error(*str));
	closedir(dir);
	if (chdir(str[0]))
		return (ft_cd_error(*str));
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (0);
	ft_update_env(data->env, "OLDPWD=", ft_getenv(data->env, "PWD"));
	ft_update_env(data->env, "PWD=", cwd);
	free(cwd);
	return (0);
}
