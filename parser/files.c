/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:18:32 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 16:42:39 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_rd_in(t_data *data, char *arg, int i)
{
	int	newfd;

	newfd = open(arg, O_RDONLY);
	if (newfd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Not such file or directory\n", 2);
		ft_free_data(data);
		exit(EXIT_FAILURE);
	}
	if (i == 0)
		data->fd_in = newfd;
	else
		data->pipes[i - 1][0] = newfd;
}

void	ft_rd_out(t_data *data, char *arg, int i)
{
	int	newfd;

	newfd = open(arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (newfd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Not such file or directory\n", 2);
		ft_free_data(data);
		exit(EXIT_FAILURE);
	}
	if (i == data->nb_pipes)
		data->fd_out = newfd;
	else
		data->pipes[i][1] = newfd;
}

void	ft_rd_append(t_data *data, char *arg, int i)
{
	int	newfd;

	newfd = open(arg, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (newfd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Not such file or directory\n", 2);
		ft_free_data(data);
		exit(EXIT_FAILURE);
	}
	if (i == data->nb_pipes)
		data->fd_out = newfd;
	else
		data->pipes[i][1] = newfd;
}

