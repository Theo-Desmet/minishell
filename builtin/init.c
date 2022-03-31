/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:57:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/31 08:42:12 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	**ft_init_env(t_list **env, char **envp)
{
	size_t	i;
	t_list	*temp;
	char	*value;
	int		lenght;

	env = malloc(sizeof(t_list));
	if (!env)
		return (NULL);
	*env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		ft_lstadd_back(env, ft_lstnew(envp[i]));
		i++;
	}
	temp = *env;
	while (temp)
	{
		value = temp->content;
		lenght = ft_strlen(value);
		temp->content = ft_strdup(value);
		temp = temp->next;
	}
	return (env);
}

t_data	*ft_init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);//modifier secu err
	data->env = ft_init_env(data->env, envp);//secu malloc
	return (data);
}
