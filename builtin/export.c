/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:28:05 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/20 14:46:04 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_add_env(t_list **env, char *str)
{
	t_list	*temp;
	char	*name;
	int	i;

	i = 0;
	temp = *env;
	name = ft_strdup(str);
	while (name[i] && name[i] != '+')
		i++;
	name[i] = '=';
	name[i + 1] = 0;
	str = &str[i + 2];
	while (temp && ft_strncmp(name, temp->content, ft_strlen(name)))
		temp = temp->next;
	if (!temp)
		ft_lstadd_back(env, ft_lstnew(ft_strjoin(name, str)));//leak ???
	else
	{
		i = 0;
		while (name[i] && name[i] != '=')
			i++;
		if (name[i] == '=')
			temp->content = ft_strjoin(temp->content, str);//leak ???
	}
}

int	ft_check_export_arg(t_list **env, char *str)
{
	size_t	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		ft_putstr_fd("minishell: `export': `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (ft_parse_add_env(env, str),2);
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			ft_putstr_fd("minishell: `export': `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
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
	char	*name2;
	size_t	i;
	int		name_lenght;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name2 = ft_strdup(str);
	name2[i] = 0;
	temp = *env;
	name_lenght = ft_strlen(name);
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
			temp->content = str;
	}
}

int 	ft_export(t_list **env, char **arg)
{
	size_t	i;
	char	*name;
	int		ret;
	int		temp;

	i = 1;
	temp = 0;
	ret = 0;
	if (env && !arg[1])
		return (ft_sort_export(env), 0);
	while (arg && arg[i])
	{
		if (ft_check_export_arg(env, arg[i]) == 0)
		{
			name = ft_name_env(arg[i]);
			ft_add_env(env, arg[i], name);
			free(name);
		}
		else
			ret = 1;
		i++;
	}
	return (ret);
}
