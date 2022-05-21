/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:35:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/20 14:48:15 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!(*args) || !args[1])
	{
		ft_printf("\n");
		return (0);
	}
	n = ft_check_option(args);
	limit = 0;
	while (args[limit])
		limit++;
	i = 1;
	if (n)
		i = 2;
	while (i < limit)
	{
		// ft_putstr(args[i]);
		ft_printf("%s", args[i]);
		if (args[++i])
			ft_printf(" ");
			// ft_putchar(' ');
	}
	if (!n)
		ft_printf("\n");
	return (0);
}
