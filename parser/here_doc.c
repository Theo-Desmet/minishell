/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:42:33 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/09 15:35:33 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_here_doc(char *limiter, char *line, int fd, int len)
{
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			close(fd);
			free(line);
			return ;
		}
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			close(fd);
			free(line);
			return ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

void	ft_get_doc(char *limiter, int nb_heredoc)
{
	char	*line;
	size_t	len;
	int		fd;
	char	*name;

	line = NULL;
	name = ft_strjoin2("/tmp/minishell", ft_itoa(nb_heredoc));
	if (!name)
		return ;
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(name);
		return ;
	}
	len = ft_strlen(limiter);
	ft_here_doc(limiter, line, fd, len);
	free(name);
}
