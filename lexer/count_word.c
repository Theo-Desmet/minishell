/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:07:19 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/25 11:07:19 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_count_word_sep(char *str, size_t *i, int mode)
{
	char	sep;

	if (mode == 1)
	{
		sep = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != sep)
			(*i)++;
		(*i)++;
	}
	if (str[*i] && !ft_issep(str[*i]))
	{
		while (str[*i] && !ft_isspace(str[*i])
			&& !ft_isspecchar(str[*i]) && !ft_issep(str[*i])
			&& !ft_ispar(str[*i]) && !(str[*i] == '&' && str[(*i) + 1] == '&'))
			(*i)++;
	}
	if (str[*i] && ft_issep(str[*i]))
		ft_count_word_sep(str, i, 0);
}

void	ft_count_word_spec(char *str, size_t *i, size_t *nb)
{
	char	sep;

	sep = 127;
	if (!ft_isspace(str[*i]))
	{
		sep = str[(*i)];
		(*nb)++;
	}
	if (ft_isspecchar(str[(*i) + 1]) && str[(*i) + 1] == sep && sep != 127)
		(*i)++;
	(*i)++;
}

void	ft_count_word(char *str, size_t *i, size_t *nb)
{
	char	sep;

	while (str[*i] && !ft_isspace(str[*i]) && !ft_isspecchar(str[*i])
		&& !ft_ispar(str[*i]) && !(str[*i] == '&' && str[(*i) + 1] == '&'))
	{
		if (ft_issep(str[*i]))
		{
			sep = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != sep)
				(*i)++;
			if (!str[*i])
				break ;
			(*i)++;
			if (str[*i] && ft_isspace(str[*i]))
				break ;
		}
		else
			(*i)++;
	}
	(*nb)++;
}

void	ft_count_var(char *str, size_t *i, size_t *nb)
{
	(*i)++;
	while (str[*i] && !ft_isspace(str[*i]) && !ft_isspecchar(str[*i])
		&& !ft_issep(str[*i]) && !ft_ispar(str[*i])
		&& !(str[*i] == '&' && str[(*i) + 1] == '&'))
		(*i)++;
	ft_count_word(str, i, nb);
}

size_t	ft_block_count(char *str)
{
	size_t	i;
	size_t	nb;

	if (!str)
		return (0);
	i = 0;
	nb = 0;
	while (str[i])
	{
		ft_skip_spaces(str, &i);
		ft_get_count(str, &i, &nb);
		ft_skip_spaces(str, &i);
	}
	return (nb);
}
