/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:28:05 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/11 09:25:18 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_export_arg(char *str)
{
	size_t	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		ft_putstr_fd("minishell: `export': `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[0] != '_'))
		{
			ft_putstr_fd("minishell: `export': `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	if ((str[i] == '=' && !str[i + 1]) || str[i] != '=')
		return (0);
	return (1);
}

char	*ft_name_env(char *str)
{
	size_t	i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_strdup(str);
	name[i + 1] = 0;
	return (name);
}

void	ft_add_env(t_list **env, char *str, char *name)
{
	t_list	*temp;
	int		name_lenght;

	temp = *env;
	name_lenght = ft_strlen(name);
	while (temp && ft_strncmp(name, temp->content, name_lenght))
		temp = temp->next;
	if (!temp)
		ft_lstadd_back(env, ft_lstnew(str));
	else
		temp->content = str;
}

t_list	**ft_export(t_list **env, char **arg)
{
	size_t	i;
	char	*name;

	i = 1;
	if (env && !arg[1])
		ft_sort_export(env);
	while (arg && arg[i])
	{
		if (ft_check_export_arg(arg[i]))
		{
			name = ft_name_env(arg[i]);
			ft_add_env(env, arg[i], name);
			free(name);
		}
		i++;
	}
	return (env);
}
