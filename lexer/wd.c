/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:47:04 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/06 12:18:57 by tdesmet          ###   ########.fr       */
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

int	ft_check_last_wd(char **tab, char *name, int i, int j)
{
	int	size_tab;
	int	size_name;

	if (tab[j + 1] && tab[j + 2])
		return (0);
	size_tab = ft_strlen(tab[j + 1]);
	i += ft_strstr_len(&name[i], tab[j + 1]);
	size_name = ft_strlen(&name[i]);
	if (size_tab != size_name)
		return (1);
	return (0);
}

void	ft_check_wildcard(t_list **wd, char **tab, char *name)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tab[j])
	{
		while (tab[j][0] == '*' && tab[j + 1] && tab[j + 1][0] == '*')
			j++;
		if (tab[j] && !ft_strcmp(tab[j], "*"))
		{
			if (!ft_strcmp(tab[j], "*") && tab[j + 1] == 0)
				break ;
			if (!ft_strstr(&name[i], tab[j + 1])
				|| ft_check_last_wd(tab, name, i, j))
				return ;
			i += ft_strstr_len(&name[i], tab[j + 1]);
		}
		else if (ft_strncmp(tab[j], &name[i], ft_strlen(tab[j])))
			return ;
		else
			i += ft_strlen(tab[j]);
		j++;
	}
	ft_lstadd_back(wd, ft_lstnew(ft_strdup(name)));
}

void	ft_sort_lst(t_list **wd, int (*comp)(char *, char *))
{
	t_list	*temp;
	t_list	*save;
	char	*str;

	temp = *wd;
	save = *wd;
	while (save)
	{
		str = "~";
		while (temp)
		{
			if (comp(temp->content, str) < 0)
			{
				str = temp->content;
				temp->content = save->content;
				save->content = str;
			}
			temp = temp->next;
		}
		save = save->next;
		temp = save;
	}
}
