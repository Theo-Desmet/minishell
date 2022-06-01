/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:08:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/01 15:34:03 by bbordere         ###   ########.fr       */
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
		ft_lstadd_back(env, ft_lstnew(name));
		return ;
	}
	free(name);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
		temp->content = ft_strjoin1(temp->content, str);
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
	while (name[i] && name[i] != '+')
		i++;
	name[i] = '=';
	name[i + 1] = 0;
	name2 = ft_strdup(name);
	name2[i] = 0;
	str = &str[i + 2];
	while (temp && (ft_strncmp(name, temp->content, ft_strlen(name))
			&& ft_strcmp(name2, temp->content)))
		temp = temp->next;
	free(name2);
	ft_parse_add_env2(env, temp, str, name);
}
