/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:01 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/01 14:46:23 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	**ft_wildcard(t_list **wd, char *str)
{
	struct dirent *fichier;
	DIR			*dir;
	size_t			i;
	char			**tab;

	dir = opendir(".");
	if (!dir)
		return (wd);//a changer
	fichier = readdir(dir);
	if (!fichier)
		return (wd);//a changer
	tab = ft_split_conserve(str, '*');
}
