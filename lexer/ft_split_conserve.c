/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_conserve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:42:07 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 12:42:32 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	ft_countword(const char *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!str || !(*str))
		return (0);
	if (c == 0)
		return (1);
	while (str[i])
	{
		if (str[i] == c || (str[i] != c
				&& (str[i + 1] == '\0' || str[i + 1] == c)))
			cnt += 1;
		i++;
	}
	return (cnt);
}

static char	**ft_malerror(char **tab, int i)
{
	while (i)
	{
		free(tab[i]);
		(i)--;
	}
	free(tab);
	return (NULL);
}

static int	ft_wrsplit(const char *str, char c, char **tab, int index[4])
{
	while (++(index[0]) < ft_countword(str, c))
	{
		index[2] = 0;
		if (str[index[1]] == c)
		{
			tab[index[0]] = malloc(sizeof(char) + 1);
			if (!tab[index[0]])
				ft_malerror(tab, index[0]);
			tab[index[0]][(index[2])++] = str[(index[1])++];
		}
		else if (str[index[1]])
		{
			index[3] = index[1];
			while (str[index[3]] != c && str[index[3]] != 0)
				(index[3])++;
			tab[index[0]] = malloc(sizeof(char) * (index[3] - index[1] + 1));
			if (!tab[index[0]])
				ft_malerror(tab, index[0]);
			while (str[index[1]] != c && str[index[1]] != 0)
				tab[index[0]][(index[2])++] = str[(index[1])++];
		}
		tab[index[0]][(index[2])++] = 0;
	}
	return (index[0]);
}

char	**ft_split_conserve(const char *str, char c)
{
	int		i;
	int		index[4];
	char	**tab;

	i = 0;
	index[0] = -1;
	index[1] = 0;
	index[2] = 0;
	index[3] = 0;
	tab = NULL;
	if (!str || *str == '\0')
	{
		tab = malloc(sizeof(char *));
		tab[0] = 0;
		return (tab);
	}
	tab = malloc(sizeof(char *) * (ft_countword(str, c) + 1));
	i = ft_wrsplit(str, c, tab, index);
	tab[i] = 0;
	return (tab);
}
