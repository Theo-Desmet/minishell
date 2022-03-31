/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:34:37 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/29 09:39:34 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	i = 0;
	ft_putstr("declare -x ");
	while (name[i] && (ft_isalnum(name[i]) || name[i] == '_'))
	{
		ft_putchar(name[i]);
		i++;
	}
	ft_putchar(name[i]);
	i++;
	ft_putchar('\"');
	while (name[i])
	{
		ft_putchar(name[i]);
		i++;
	}
	ft_putstr("\"\n");
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
