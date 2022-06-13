/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:34:09 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/13 07:57:34 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_all(t_data *data, char **args, int rtn, char *command)
{
	free(command);
	ft_close(&data->fd_in, &data->fd_out);
	ft_free_data(data);
	ft_free_tab((void **)args);
	exit(rtn);
}

int	ft_exit_num_err(char **args, int i)
{
	if ((args[1][i] && !args[2]) || !args[1][0])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (1);
	}
	return (0);
}

int	ft_exit_too_many_arg(char **args)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_global.rtn_val = 1;
		return (1);
	}
	return (0);
}

void	ft_exit(t_data *data, char **args, char *command)
{
	char	*rtn;
	int		i;

	i = 0;
	if (!args || !args[1])
	{
		ft_printf("exit\n");
		ft_free_all(data, args, g_global.rtn_val, command);
	}
	rtn = args[1];
	while (rtn[i] && (rtn[i] == 32 || rtn[i] == '\t' || rtn[i] == '\n'
			|| rtn[i] == '\r' || rtn[i] == '\v' || rtn[i] == '\f'))
		i++;
	if (rtn[i] && (rtn[i] == '-' || rtn[i] == '+'))
		i++;
	while (rtn[i] && ft_isdigit(rtn[i]))
		i++;
	if (ft_exit_num_err(args, i))
		ft_free_all(data, args, 2, command);
	if (ft_exit_too_many_arg(args))
		return ;
	ft_free_all(data, args, ft_atoi(args[1]), command);
}
