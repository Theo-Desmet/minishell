/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:35:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/24 09:55:51 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_option(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (!args || !(*args))
		return (0);
	while (args[i])
	{
		if (args[i][0] != '-')
			return (i);
		while (args[i][j] == 'n')
			j++;
		if (args[i][j])
			return (i);
		i++;
		j = 1;
	}
	return (i);
}

int	ft_echo(char **args)
{
	int	n;
	int	limit;
	int	i;

	if (!(*args) || !args[1])
	{
		ft_printf("\n");
		return (0);
	}
	n = ft_check_option(args);
	limit = 0;
	while (args[limit])
		limit++;
	i = n;
	while (i < limit)
	{
		ft_printf("%s", args[i]);
		if (args[++i])
			ft_printf(" ");
	}
	if (n <= 1)
		ft_printf("\n");
	return (0);
}
