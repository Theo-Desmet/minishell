/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:05:22 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/25 11:05:22 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_isspecchar(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	ft_issep(int c)
{
	return (c == '\"' || c == '\'');
}

int	ft_ispar(int c)
{
	return (c == '(' || c == ')');
}

void	ft_skip_spaces(char *str, size_t *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

void	ft_free(void **tab)
{
	int	i;

	i = -1;
	if (!*tab)
	{
		free(tab);
		return ;
	}
	while (tab[++i])
		if (tab[i])
			free(tab[i]);
	free(tab);
	tab = NULL;
}
