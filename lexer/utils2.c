/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:28:22 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/06 11:09:13 by tdesmet          ###   ########.fr       */
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
