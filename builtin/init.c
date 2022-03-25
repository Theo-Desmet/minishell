/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:57:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/25 11:12:41 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_path(t_data *data)
{
	char	*buf1;
	char	*buf2;

	buf1 = NULL;
	buf2 = NULL;
	data->prev_path = getcwd(buf1, 0);
	data->actu_path = getcwd(buf2, 0);
}

t_list	**ft_init_env(t_list **env, char **envp)
{
	size_t		i;

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
	return (env);
}

t_data	*ft_init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if(!data)
		return (NULL);//modifier secu err
	ft_init_path(data);
	data->env = ft_init_env(data->env, envp);//secu malloc
	return (data);
}
