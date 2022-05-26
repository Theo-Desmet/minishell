/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:07:21 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 15:55:24 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

size_t	ft_size_str(char *str, int i)
{
	size_t	size;
	char	sep;

	if (ft_strlen(str) == 1)
		return (1);
	size = 0;
	while (str[i + size] && !ft_isspace(str[i + size])
		&& !ft_isspecchar(str[i + size]) && !ft_ispar(str[i + size])
		&& !(str[i + size] == '&' && str[i + 1 + size] == '&'))
	{
		if (ft_issep(str[i + size]))
		{
			sep = str[i + size++];
			while (str[i + size] && str[i + size] != sep)
				size++;
			if (str[i + size])
				size++;
			if (str[i + size] && ft_isspace(str[i + size]))
				break ;
		}
		else
			size++;
	}
	return (size);
}

size_t	ft_size_var(char *str, size_t i)
{
	size_t	size;

	i++;
	size = 0;
	while (str[i] && !ft_isspace(str[i]) && !ft_isspecchar(str[i])
		&& !ft_issep(str[i]) && !ft_ispar(str[i]) && !(str[i] == '&'
			&& str[(i) + 1] == '&'))
	{
		i++;
		size++;
	}
	return (size + ft_size_str(str, i) + 1);
}

size_t	ft_word_size(char *str, size_t i)
{
	size_t	size;

	size = 0;
	if (str[i])
	{
		if ((str[i + 1] && str[i] == '$' && !ft_issep(str[i + 1]))
			|| (str[i] == '&' && str[i + 1] != '&' && !ft_issep(str[i + 1])
				&& !ft_isspace(str[i + 1]) && !ft_isspecchar(str[i + 1])
				&& !ft_ispar(str[i + 1])))
			return (ft_size_var(str, i));
		else if (str[i + 1] && str[i] == '&' && str[i + 1] == '&')
			return (2);
		else if ((ft_ispar(str[i])) || (str[i + 1] && ft_isspecchar(str[i])
				&& !ft_isspecchar(str[i + 1]))
			|| (ft_isspecchar(str[i]) && str[i + 1] != str[i]))
			return (1);
		else if (str[i + 1] && ft_isspecchar(str[i])
			&& ft_isspecchar(str[i + 1]))
			return (2);
		else
			return (ft_size_str(str, i));
	}
	return (size);
}

void	ft_fill_tab(char *str, size_t *i, size_t *j, char **res)
{
	char	*temp;

	if (ft_issep(str[*j]))
		ft_skip_sep(str, j);
	else
		while (str[*j] && ft_isspace(str[*j]) && !ft_issep(str[*j])
			&& !ft_ispar(str[*j]))
			(*j)++;
	if (ft_issep(str[*j]))
		ft_skip_sep(str, j);
	temp = ft_substr(str, *j, ft_word_size(str, *j));
	if (!temp)
	{
		ft_free_tab((void **)res);
		return ;
	}
	res[*i] = temp;
	*j += ft_word_size(str, *j);
	(*i)++;
}

char	**ft_lexer(char *str)
{
	char	**res;
	size_t	i;
	size_t	j;
	size_t	nb;

	i = 0;
	j = 0;
	nb = ft_block_count(str);
	res = malloc((nb + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < nb)
		ft_fill_tab(str, &i, &j, res);
	res[nb] = NULL;
	return (res);
}
