/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:42:33 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/25 15:36:44 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_heredoc(int signal)
{
	if (signal == SIGINT)
		g_global.rtn_val = -1;
}

void	ft_exit_here_doc(t_data *data, int *fd, int rtn)
{
	ft_close(fd, NULL);
	free(data->here_doc);
	data->here_doc = NULL;
	ft_close(&data->fd_in, &data->fd_out);
	ft_free_data(data);
	exit(rtn);
}

void	ft_here_doc(t_data *data, char *limiter, char *line, int *fd)
{
	size_t	len;

	len = ft_strlen(limiter);
	signal(SIGINT, ft_sig_heredoc);
	while (1)
	{
		if (g_global.rtn_val == -1)
			ft_exit_here_doc(data, fd, SIGINT);
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!line)
			ft_quit_here_doc(data, fd, line, limiter);
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
			ft_quit_here_doc(data, fd, line, NULL);
		write(*fd, line, ft_strlen(line));
		free(line);
	}
	ft_quit_here_doc(data, fd, NULL, NULL);
}

int	ft_here(t_data *data, char *limiter, int nb_heredoc)
{
	char	*line;
	int		fd;

	line = NULL;
	data->here_doc = ft_strjoin2("/tmp/minishell", ft_itoa(nb_heredoc));
	if (!data->here_doc)
		return (-1);
	fd = open(data->here_doc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(data->here_doc);
		data->here_doc = NULL;
		return (-1);
	}
	ft_here_doc(data, limiter, line, &fd);
	free(data->here_doc);
	data->here_doc = NULL;
	return (0);
}

int	ft_get_doc(t_data *data, char *limiter, int nb_heredoc)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
		ft_here(data, limiter, nb_heredoc);
	waitpid(pid, &status, 0);
	return (ft_get_return_val(status));
}
