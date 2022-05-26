/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 08:10:05 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/26 10:05:55 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_unset_arg(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (NULL);
		}
		i++;
	}
	str = ft_strjoin(str, "=");
	return (str);
}

char	*ft_get_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_strdup(str);
	name[i] = 0;
	return (name);
}

int	ft_check_first_env(t_list **env, t_list *temp, char *str, char *name)
{
	if (temp && (!ft_strncmp(temp->content, str, ft_strlen(str))
			|| !ft_strcmp(name, temp->content)))
	{
		*env = (*env)->next;
		free(temp->content);
		free(temp);
		free(name);
		return (1);
	}
	return (0);
}

void	ft_del_env(t_list **env, char *str)
{
	t_list	*temp;
	t_list	*save;
	int		name_lenght;
	char	*name;

	name = ft_get_name(str);
	temp = *env;
	name_lenght = ft_strlen(str);
	if (ft_check_first_env(env, temp, str, name))
		return ;
	while (temp->next && ft_strncmp(temp->next->content, str, name_lenght)
		&& ft_strcmp(name, temp->next->content))
		temp = temp->next;
	free(name);
	if (!temp->next)
		return ;
	else
	{
		save = temp->next;
		temp->next = temp->next->next;
		free(save->content);
		free(save);
	}
}

int	ft_unset(t_list **env, char **arg)
{
	size_t	i;
	char	*name;
	int		ret;

	i = 1;
	ret = 0;
	while (arg && arg[i] && env && *env)
	{
		name = NULL;
		name = ft_check_unset_arg(arg[i]);
		if (name)
		{
			ft_del_env(env, name);
			free(name);
		}
		else
			ret = 1;
		i++;
	}
	return (ret);
}
