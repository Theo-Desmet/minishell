/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 04:31:51 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/17 05:04:36 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
int	ft_parse_add_env(t_list **env, char *str)
{
	char	*name;
	char	*arg;
	int	i;

	i = 0;
	name = ft_strdup(str);
	while (name[i] && name[i] != '+')
		i++;
	name[i] = '=';
	name[i + 1] = '0';
	arg = str[i + 2];
	while (temp && (ft_strncmp(name, temp->content, name_lenght)
			&& ft_strcmp(name2, temp->content)))
		temp = temp->next;
	if (!temp)
		ft_lstadd_back(env, ft_lstnew(str));
	else
	{
		i = 0;
		while (name[i] && name[i] != '=')
			i++;
		if (name[i] == '=')
			temp->content = ft_strjoin(temp->content, arg);//leak ???
	}
}
*/
