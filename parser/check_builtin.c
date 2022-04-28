/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:19:27 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/20 15:26:45 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isbuiltin(char *val)
{
	char	**tab;

	tab = ft_lexer(val);
	if (!tab || !*tab)
	{
		if (tab)
			free(tab);
		return (0);
	}
	if (ft_strnstr(tab[0], "echo", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "cd", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "pwd", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "export", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "unset", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "env", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "exit", ft_strlen(tab[0])))
	{
		ft_free((void **)tab);
		return (1);
	}
	ft_free((void **)tab);
	return (0);
}

void	ft_check_builtin(t_token **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_isbuiltin(tokens[i]->val))
			tokens[i]->type = BUILDIN;
		i++;
	}
}
