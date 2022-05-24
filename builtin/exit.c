/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:34:09 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/24 09:27:22 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_all(char *rtn)
{
	exit(ft_atoi(rtn));
}

void	ft_exit(char **args)
{
	char	*rtn;
	int 	i;

	i = 0;
	if (!args || !args[1])
		rtn = ft_itoa(g_global->rtn_val);
	else
		rtn = args[1];
	ft_printf("exit\n");
	while (rtn[i] && ft_isdigit(rtn[i]))
		i++;
	if (rtn[i])
	{
		rtn = ft_itoa(g_global->rtn_val);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		ft_free_all(rtn);
	}
	if (args[1] && args[2])
	{
		rtn = ft_itoa(g_global->rtn_val);
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		ft_free_all(rtn);
	}
	ft_free_all(rtn);
}
