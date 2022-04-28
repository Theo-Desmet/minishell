/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:36:02 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/19 21:36:02 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*ft_get_var(t_list **env, char *str)
{
	t_list	*temp;
	size_t	len;
	char	*content;

	if (!env || !(*env))
		return (ft_return_dup(str, NULL));
	if (!ft_strncmp(str, "?", 1))
		return (ft_expand_return_code(str));
	temp = *env;
	len = ft_strlen(str);
	while (temp)
	{
		content = temp->content;
		if (!ft_strncmp(str, content, len) && content[len] == '=')
			return (ft_return_dup(str, &content[len + 1]));
		temp = temp->next;
	}
	return (ft_return_dup(str, ""));
}

char	**ft_extract_var(char *str)
{
	char	**res;
	size_t	i;
	size_t	j;
	size_t	nb;

	i = 0;
	j = 0;
	nb = ft_count_vars(str);
	res = malloc(sizeof(char *) * (nb + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] != '$')
		{
			res[j] = ft_substr(str, i, ft_len_vars(str, i));
			j++;
		}
		i++;
	}
	res[nb] = NULL;
	return (res);
}

char	*ft_var(char *res, t_temp *temp)
{
	res = ft_strjoin2(res, ft_get_var(temp->env, temp->vars[(temp->j)++] + 1));
	while (temp->str[(temp->i) + 1] && !ft_isspace(temp->str[(temp->i) + 1])
		&& !ft_isspecchar(temp->str[(temp->i) + 1])
		&& !ft_issep(temp->str[(temp->i) + 1])
		&& temp->str[(temp->i) + 1] != '$'
		&& !ft_ispar(temp->str[(temp->i) + 1]))
			(temp->i)++;
	(temp->i)++;
	return (res);
}

char	*ft_str_var(char *res, t_temp *temp)
{
	(temp->i)++;
	while (temp->str[(temp->i)] && temp->str[(temp->i)] != '\"')
	{
		if (temp->str[(temp->i) + 1] && temp->str[(temp->i)] == '$'
			&& temp->str[(temp->i) + 1] != '$'
			&& !ft_issep(temp->str[(temp->i) + 1]))
			res = ft_var(res, temp);
		else
			res = ft_charjoin(res, temp->str[(temp->i)++]);
	}
	(temp->i)++;
	return (res);
}

char	*ft_get_str(char *str, int mode)
{
	size_t	i;
	char	*res;

	res = NULL;
	i = 1;
	while (str[i] && str[i] != '\'')
	{
		res = ft_charjoin(res, str[i]);
		i++;
	}
	if (mode)
		free(str);
	return (res);
}
