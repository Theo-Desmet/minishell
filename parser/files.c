/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:18:32 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/05 12:14:58 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_not_such_file(t_data *data, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Not such file or directory\n", 2);
	ft_free_data(data);
	exit(EXIT_FAILURE);
}

void	ft_rd_in(t_data *data, char *arg, int i)
{
	int	newfd;

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
