/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:18:32 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/11 18:06:46 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_search_in_directory(char *cmd);

int	ft_wd_file(t_data *data, char **var)
{
	ft_wildcard(data->wd, *var);
	if (ft_lstsize(*data->wd) == 1)
	{
		free(*var);
		*var = ft_strdup((*data->wd)->content);
		ft_lstclear(data->wd, free);
		return (0);
	}
	else if (ft_lstsize(*data->wd) == 0)
		return (0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*var, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	ft_lstclear(data->wd, free);
	return (-1);
}

int	ft_check_files(t_data *data, char **arg, int mode)
{
	int	wd;
	int	fd;

	wd = 0;
	fd = -1;
	if (ft_strchr(*arg, '*'))
		wd = ft_wd_file(data, arg);
	if (wd == 0)
		fd = open(*arg, mode, 0664);
	if (fd == -1)
	{
		if (wd == 0)
			ft_search_in_directory(*arg);
		if (!data->nb_pipes)
			ft_close(&data->fd_in, &data->fd_out);
		return (-1);
	}
	return (fd);
}

void	ft_rd_in(t_data *data, char **arg, int i)
{
	int	newfd;

	newfd = ft_check_files(data, arg, O_RDONLY);
	if (i == 0)
	{
		ft_close(&data->fd_in, NULL);
		data->fd_in = newfd;
	}
	else
	{
		ft_close(&data->pipes[i - 1][0], NULL);
		data->pipes[i - 1][0] = newfd;
	}
}

void	ft_rd_out(t_data *data, char **arg, int i)
{
	int	newfd;

	newfd = ft_check_files(data, arg, O_CREAT | O_RDWR | O_TRUNC);
	if (i == data->nb_pipes)
	{
		ft_close(&data->fd_out, NULL);
		data->fd_out = newfd;
	}
	else
	{
		ft_close(&data->pipes[i][1], NULL);
		data->pipes[i][1] = newfd;
	}
}

void	ft_rd_append(t_data *data, char **arg, int i)
{
	int	newfd;

	newfd = ft_check_files(data, arg, O_CREAT | O_RDWR | O_APPEND);
	if (i == data->nb_pipes)
	{
		ft_close(&data->fd_out, NULL);
		data->fd_out = newfd;
	}
	else
	{
		ft_close(&data->pipes[i][1], NULL);
		data->pipes[i][1] = newfd;
	}
}
