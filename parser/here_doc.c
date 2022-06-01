/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:42:33 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/01 18:37:16 by bbordere         ###   ########.fr       */
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
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	len = ft_strlen(limiter);
	ft_here_doc(limiter, line, fd, len);
	free(name);
}

int	*ft_check_last_heredoc2(t_data *data, t_token **args, int cnt[2])
{
	int		i;
	int		multi_doc;

	i = -1;
	multi_doc = 0;
	while (args[++i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == R_HERE_DOC)
		{
			if (multi_doc)
				unlink(ft_strjoin2("/tmp/minishell",
						ft_itoa(data->act_heredoc)));
			data->act_heredoc++;
			cnt[0] = i;
			multi_doc = 1;
		}
		if (args[i]->type == R_IN)
			cnt[1] = i;
	}
	return (cnt);
}

char	*ft_check_last_heredoc(t_data *data, t_token **args)
{
	int		cnt[2];
	char	*name;

	cnt[0] = -1;
	cnt[1] = -1;
	ft_check_last_heredoc2(data, args, cnt);
	name = ft_strjoin2("/tmp/minishell", ft_itoa(data->act_heredoc));
	if (cnt[0] > cnt[1])
		return (name);
	else
		return (free(name), NULL);
}
