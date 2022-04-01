/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:35:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/31 15:56:30 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_option(char **args)
{
	if (!args || !(*args))
		return (0);
	return (!ft_strncmp(*args, "-n", ft_strlen(*args)));
}

int	ft_echo(char **args)
{
	int	n;
	int	limit;
	int	i;

	if (!args || !(*args))
	{
		printf("\n");
		return (1);
	}
	n = ft_check_option(args);
	limit = 0;
	while (args[limit])
		limit++;
	i = 0;
	if (n)
		i = 1;
	while (i < limit)
	{
		ft_putstr(args[i]);
		if (args[++i])
			ft_putchar(' ');
	}
	if (!n)
		ft_putstr("\n");
	return (1);
}
