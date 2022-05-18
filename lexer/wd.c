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

int		ft_strcasecmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && 
		ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
		return (ft_free_tab((void **)tab), 0);
	while (fichier)
	{
		if (fichier->d_name[0] != '.')
			ft_check_wildcard(wd, tab, fichier->d_name);
		fichier = readdir(dir);
	}
	ft_free_tab((void **)tab);
	ft_sort_lst(wd, ft_strcasecmp); //BB swap bb (case opp) Bb > bB 
	if (!closedir(dir))
		return (0);
	return (1);
}