/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:34:37 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/20 14:51:51 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_size(t_list **env)
{
	t_list	*temp;
	size_t	i;

	i = 0;
	temp = *env;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_print_export(char *name)
{
	size_t	i;
	int		egal;

	i = 0;
	egal = 0;
	ft_printf("declare -x ");
	while (name[i] && (ft_isalnum(name[i]) || name[i] == '_'))
	{
		ft_printf("%c", name[i]);
		i++;
	}
	ft_printf("%c", name[i]);
	if (name[i] == '=')
		ft_printf("\"");
	else
		egal = 1;
	i++;
	while (name[i])
	{
		ft_printf("%c", name[i]);
		i++;
	}
	if (!egal)
		ft_printf("\"");
	ft_printf("\n");
}

void	ft_sort_export(t_list **env)
{
	t_list	*temp;
	char	*name;
	char	*name_save;
	size_t	i;

	i = ft_env_size(env);
	temp = *env;
	name = "~";
	name_save = "\0";
	while (i > 0)
	{
		if (ft_strcmp(temp->content, name) < 0
			&& ft_strcmp(temp->content, name_save) > 0)
			name = temp->content;
		else
			temp = temp->next;
		if (!temp)
		{
			temp = *env;
			name_save = name;
			ft_print_export(name);
			name = "~";
			i--;
		}
	}
}
