/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 10:57:15 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/14 17:27:05 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findsep(char str, char c)
{
	if (c == str)
		return (1);
	else
		return (0);
}

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
		if (ft_findsep(str[i], c) == 0 && (ft_findsep(str[i + 1], c) == 1
				|| str[i + 1] == '\0'))
			cnt++;
		i++;
	}
	return (cnt);
}

static char	**ft_malerror(char **tab, int *i)
{
	while (*i)
	{
		free(tab[*i]);
		i--;
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
		while (ft_findsep(str[*j], c) == 1)
			*j += 1;
		temp = *j;
		while (ft_findsep(str[temp], c) == 0 && str[temp] != 0)
			temp++;
		tab[i] = malloc(sizeof(char) * (temp - *j + 1));
		if (!tab[i])
			ft_malerror(tab, &i);
		while (ft_findsep(str[*j], c) == 0 && str[*j] != 0)
		{
			tab[i][k] = str[*j];
			*j += 1;
			k++;
		}
		tab[i][k] = 0;
	}
	return (i);
}

char	**ft_split(const char *str, char c)
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
