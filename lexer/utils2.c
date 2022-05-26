/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:28:22 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 16:03:50 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_get_count(char *str, size_t *i, size_t *nb)
{
	if ((str[*i] == '&' && str[*i + 1] == '&')
		|| (str[*i] && ft_ispar(str[*i])))
	{
		*i = *i + 1 + !(str[*i] && ft_ispar(str[*i]));
		(*nb)++;
	}
	else if (str[*i] == '$' || (str[*i] == '&' && str[*i + 1] != '&'
			&& !ft_issep(str[*i + 1]) && !ft_isspace(str[*i + 1])
			&& !ft_isspecchar(str[*i + 1]) && !ft_ispar(str[*i + 1])))
		ft_count_var(str, i, nb);
	else if (str[*i] && ft_isspecchar(str[*i]))
		ft_count_word_spec(str, i, nb);
	else if (str[*i])
		ft_count_word(str, i, nb);
}

int	ft_isfulldollar(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '$' && !ft_issep(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcasecmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_check_wildcard(t_list **wd, char **tab, char *name)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tab[j])
	{
		while (tab[j][0] == '*' && tab[j + 1] && tab[j + 1][0] == '*')
			j++;
		if (tab[j] && !ft_strcmp(tab[j], "*"))
		{
			if (!ft_strcmp(tab[j], "*") && tab[j + 1] == 0)
				break ;
			if (!ft_strstr(&name[i], tab[j + 1]))
				return ;
			i += ft_strstr_len(&name[i], tab[j + 1]);
		}
		else if (ft_strncmp(tab[j], &name[i], ft_strlen(tab[j])))
			return ;
		else
			i += ft_strlen(tab[j]);
		j++;
	}
	ft_lstadd_back(wd, ft_lstnew(ft_strdup(name)));
}

void	ft_sort_lst(t_list **wd, int (*comp)(char *, char *))
{
	t_list	*temp;
	t_list	*save;
	char	*str;

	temp = *wd;
	save = *wd;
	while (save)
	{
		str = "~";
		while (temp)
		{
			if (comp(temp->content, str) < 0)
			{
				str = temp->content;
				temp->content = save->content;
				save->content = str;
			}
			temp = temp->next;
		}
		save = save->next;
		temp = save;
	}
}
