/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:01 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/07 11:36:20 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			if (!ft_strstr(&name[i], tab[j + 1]))
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

void	ft_free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_sort_lst(t_list **wd)
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
			if (ft_strcmp(temp->content, str) < 0)
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

int	ft_wildcard(t_list **wd, char *str)
{
	struct dirent *fichier;
	DIR			*dir;
	char			**tab;

	dir = opendir(".");
	if (!dir)
		return (0);//a changer
	fichier = readdir(dir);
	if (!fichier)
		return (0);//a changer
	tab = ft_split_conserve(str, '*');
	if (!tab)
		return (ft_free_tab(tab), 0);
	while (fichier)
	{
		ft_check_wildcard(wd, tab, fichier->d_name);
		fichier = readdir(dir);
	}
	ft_free_tab(tab);
	ft_sort_lst(wd);
	if (!closedir(dir))
		return (0);
	return (1);
}
