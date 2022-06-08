/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:18:32 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/08 17:14:19 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_wd_file(t_data *data, char *var)
{
	ft_wildcard(data->wd, var);
	if (ft_lstsize(*data->wd) == 1)
	{
		free(var);
		var = ft_strdup((*data->wd)->content);
		ft_lstclear(data->wd, free);
		return ;
	}
	else if (ft_lstsize(*data->wd) == 0)
		return ;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	ft_lstclear(data->wd, free);
}

void	ft_not_such_file(t_data *data, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Not such file or directory\n", 2);
	(void)data;
}

void	ft_rd_in(t_data *data, char *arg, int i)
{
	int	newfd;

	if (ft_strchr(arg, '*'))
		ft_wd_file(data, arg);
	newfd = open(arg, O_RDONLY);
	if (newfd < 0)
		ft_not_such_file(data, arg);
	if (i == 0)
	{
		close(data->fd_in);
		data->fd_in = newfd;
	}
	else
	{
		close(data->pipes[i - 1][0]);
		data->pipes[i - 1][0] = newfd;
	}
}

void	ft_rd_out(t_data *data, char *arg, int i)
{
	int	newfd;

	if (ft_strchr(arg, '*'))
		ft_wd_file(data, arg);
	newfd = open(arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (newfd < 0)
		ft_not_such_file(data, arg);
	if (i == data->nb_pipes)
	{
		close(data->fd_out);
		data->fd_out = newfd;
	}
	else
	{
		close(data->pipes[i][1]);
		data->pipes[i][1] = newfd;
	}
}

void	ft_rd_append(t_data *data, char *arg, int i)
{
	int	newfd;

	if (ft_strchr(arg, '*'))
		ft_wd_file(data, arg);
	newfd = open(arg, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (newfd < 0)
		ft_not_such_file(data, arg);
	if (i == data->nb_pipes)
	{
		close(data->fd_out);
		data->fd_out = newfd;
	}
	else
	{
		close(data->pipes[i][1]);
		data->pipes[i][1] = newfd;
	}
}
