/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 09:05:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/13 10:43:32 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malerror(char **tab, int i)
{
	while (i)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

static int	ft_wrsplit(const char *str, char c, char **tab, int index[5])
{
	while (++(index[0]) < index[4])
	{
		index[2] = 0;
		if (str[index[1]])
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

char	**ft_splitn(const char *str, char c, int n)
{
	int		i;
	int		index[5];
	char	**tab;

	i = 0;
	index[0] = -1;
	index[1] = 0;
	index[2] = 0;
	index[3] = 0;
	index[4] = n;
	tab = NULL;
	if (!str || *str == '\0')
	{
		tab = malloc(sizeof(char *));
		tab[0] = 0;
		return (tab);
	}
	tab = malloc(sizeof(char *) * n + 1);
	i = ft_wrsplit(str, c, tab, index);
	tab[i] = 0;
	return (tab);
}

