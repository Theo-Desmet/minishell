/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:23:23 by bbordere          #+#    #+#             */
/*   Updated: 2021/12/02 12:02:05 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_all(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

static int	ft_words_count(char const *str, char sep)
{
	size_t	i;
	int		word;

	i = 0;
	word = 0;
	while (str[i])
	{		
		while (str[i] == sep && str[i])
			i++;
		if (str[i] != sep && str[i])
			word++;
		while (str[i] != sep && str[i])
			i++;
	}
	return (word);
}

static int	ft_word_len(char const *str, char sep, size_t index)
{
	size_t	i;

	i = 0;
	while (str[index + i] && str[index + i] != sep)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*temp;
	size_t	i2;
	int		i;

	i = -1;
	i2 = 0;
	res = malloc((ft_words_count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (++i < ft_words_count(s, c))
	{
		while (s[i2] && s[i2] == c)
			i2++;
		temp = ft_substr(s, i2, ft_word_len(s, c, i2));
		if (!temp)
		{
			ft_free_all(res, i);
			return (NULL);
		}
		res[i] = temp;
		i2 += ft_word_len(s, c, i2);
	}
	res[i] = NULL;
	return (res);
}
