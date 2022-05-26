/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:47:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/24 12:47:04 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_strstr_len(const char *s1, const char *s2)
{
	size_t		i;
	size_t		temp;
	int			j;

	i = 0;
	if (!s2 || !(*s2))
		return (i);
	while (s1[i])
	{
		temp = i;
		j = 0;
		while (s2[j] && s1[temp] == s2[j])
		{
			temp++;
			j++;
			if (s2[j] == 0)
				return (i);
		}
		i++;
	}
	return (0);
}

int	ft_wildcard(t_list **wd, char *str)
{
	struct dirent	*fichier;
	DIR				*dir;
	char			**tab;

	dir = opendir(".");
	if (!dir)
		return (0);
	fichier = readdir(dir);
	if (!fichier)
		return (0);
	tab = ft_split_conserve(str, '*');
	if (!tab)
		return (ft_free_tab((void **)tab), 0);
	while (fichier)
	{
		if (fichier->d_name[0] != '.')
			ft_check_wildcard(wd, tab, fichier->d_name);
		fichier = readdir(dir);
	}
	ft_free_tab((void **)tab);
	ft_sort_lst(wd, ft_strcasecmp);
	if (!closedir(dir))
		return (0);
	return (1);
}
