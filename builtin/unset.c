/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 08:10:05 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/20 14:46:16 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_unset_arg(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]))
		{
			ft_putstr_fd("minishell: `unset': `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (NULL);
		}
		i++;
	}
	str = ft_strjoin(str, "=");
	return (str);
}

void	ft_del_env(t_list **env, char *str)
{
	t_list	*temp;
	t_list	*save;
	int		name_lenght;

	temp = *env;
	name_lenght = ft_strlen(str);
	if (temp->next && !ft_strncmp(temp->next->content, str, name_lenght))
	{
		*env = (*env)->next;
		free(temp->content);
		free(temp);
		return ;
	}
	while (temp->next && ft_strncmp(temp->next->content, str, name_lenght))
		temp = temp->next;
	if (!temp->next)
		return ;
	else
	{
		save = temp->next;
		temp->next = temp->next->next;
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
	while (arg && env && arg[i])
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
