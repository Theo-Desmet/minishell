/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_conserve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:48:03 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/01 14:48:53 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(const char *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!str || !*str)
		return (0);
	if (c == 0)
		return (1);
	while (str[i] && str)
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			cnt += 1;
		i++;
	}
	return (cnt);
}

static char	**ft_malerror(char **tab, int *i)
{
	while (*i)
	{
		free(tab[*i]);
		(*i)--;
	}
	free(tab);
	return (NULL);
}

static int	ft_wrsplit(const char *str, char c, char **tab, int *j)
{
	int	k;
	int	temp;
	int	i;

	i = -1;
	while (++i < ft_countword(str, c))
	{
		k = 0;
		while (str[*j] == c)
		{
			*j += 1;
		}
		temp = *j;
		while (str[temp] != c && str[temp] != 0)
			temp++;
		tab[i] = malloc(sizeof(char) * (temp - *j + 1));
		if (!tab[i])
			ft_malerror(tab, &i);
		while (str[*j] != c && str[*j] != 0)
			tab[i][k++] = str[(*j)++];
		tab[i][k] = 0;
	}
	return (i);
}

char	**ft_split_conserve(const char *str, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	tab = NULL;
	if (!str || *str == '\0')
	{
		tab = malloc(sizeof(char *));
		tab[0] = 0;
		return (tab);
	}
	tab = malloc(sizeof(char *) * (ft_countword(str, c) + 1));
	i = ft_wrsplit(str, c, tab, &j);
	tab[i] = 0;
	return (tab);
}

