/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:28:05 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/25 15:46:36 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_export_arg(char *str)
{
	size_t	i;

	if (!ft_isalpha(str[0]))
		return (0); //bash: str: event not found
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (0);//bash: &str[i]: event not found
		i++;
	}
	if (str[i] == '=' && !str[i + 1])
		return (0);
	return (1);
}

char	*ft_name_env(char *str)
{
	size_t	i;
	char 	*name;

	i = 0;
	while (str[i] != '=')
		i++;
	name = ft_strdup(str);
	name[i + 1] = 0;
	return (name);
}

t_list	**ft_add_env(t_list **env, char *str, char *name)
{
	t_list	*temp;
	int		name_lenght;

	temp = *env;
	name_lenght = ft_strlen(name);
	while (temp && ft_strncmp(name, temp->content, name_lenght))
		temp = temp->next;
	if (!temp)
		ft_lstadd_front(env, ft_lstnew(str));//add front a la place de back car back marche pas
	else
		temp->content = str;
	return (env);	
}

t_list	**ft_export(t_list **env, char **arg)
{
	size_t	i;
	char	*name;

	i = 0;
	while (arg && arg[i])
	{
		if (ft_check_export_arg(arg[i]))
		{
			name = ft_name_env(arg[i]);
			ft_add_env(env, arg[i], name);
		}
		i++;
	}
	return (env);
}
