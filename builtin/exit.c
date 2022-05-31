/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:34:09 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/31 15:58:18 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_all(t_data *data, char **args, int rtn)
{
	ft_free_data(data);
	ft_free_tab((void **)args);
	exit(rtn);
}

void	ft_exit_chiant(t_data *data, char **args, char *rtn, int i)
{
	if (rtn[i])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_all(data, args, g_global.rtn_val);
	}
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_free_all(data, args, g_global.rtn_val);
	}
}

void	ft_exit(t_data *data, char **args, char *command)
{
	char	*rtn;
	int		i;

	i = 0;
	ft_printf("exit\n");
	free(command);
	if (!args || !args[1])
		ft_free_all(data, args, g_global.rtn_val);
	rtn = args[1];
	while (rtn[i] && ft_isdigit(rtn[i]))
		i++;
	ft_exit_chiant(data, args, rtn, i);
	ft_free_all(data, args, ft_atoi(rtn));
}
