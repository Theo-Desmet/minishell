/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:08:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/09 10:41:13 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_add_env2(t_list **env, t_list *temp, char *str, char *name)
{
	int		i;

	i = 0;
	if (!temp)
	{
		name = ft_strjoin1(name, str);
		if (!name)
			return ;
		ft_lstadd_back(env, ft_lstnew(name));
		return ;
	}
	free(name);
	while (((char *)temp->content)[i] && ((char *)temp->content)[i] != '=')
		i++;
	if (!((char *)temp->content)[i])
	{
		name = ft_strjoin1(temp->content, "=");
		if (name)
			temp->content = name;
		return ;
	}
	name = ft_strjoin1(temp->content, str);
	if (name)
		temp->content = name;
	return ;
}

char	*ft_get_name_norme(char *name, char *name2, int i)
{
	name[i] = '=';
	name[i + 1] = 0;
	name2 = ft_strdup(name);
	if (!name2)
	{
		free(name);
		return (NULL);
	}
	name2[i] = 0;
	return (name2);
}

void	ft_parse_add_env(t_list **env, char *str)
{
	t_list	*temp;
	char	*name;
	char	*name2;
	int		i;

	i = 0;
	temp = *env;
	name = ft_strdup(str);
	name2 = NULL;
	if (!name)
		return ;
	while (name[i] && name[i] != '+')
		i++;
	name2 = ft_get_name_norme(name, name2, i);
	if (!name2)
		return ;
	str = &str[i + 2];
	while (temp && (ft_strncmp(name, temp->content, ft_strlen(name))
			&& ft_strcmp(name2, temp->content)))
		temp = temp->next;
	free(name2);
	ft_parse_add_env2(env, temp, str, name);
}
