/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:42:33 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 16:43:35 by bbordere         ###   ########.fr       */
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
			if (close(fd))
				continue; //error close
			return ;
			//warning error
		}
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			if (close(fd))
				continue; //error close
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
	name = ft_strjoin("/tmp/minishell", ft_itoa(nb_heredoc));
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("fuck");
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(limiter);
	ft_here_doc(limiter, line, fd, len);
	free(name);
}

char	*ft_check_last_heredoc(t_data *data, t_token **args)
{
	int		i;
	int		cnth;
	int		cnti;
	char	*name;

	i = -1;
	cnth = -1;
	cnti = -1;
	name = NULL;
	while (args[++i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == R_HERE_DOC)
		{
			data->act_heredoc++;
			cnth = i;
		}
		if (args[i]->type == R_IN)
			cnti = i;
	}
	name = ft_strjoin2("/tmp/minishell", ft_itoa(data->act_heredoc));
	if (cnth > cnti)
		return (name);
	else
		return (free(name), NULL);
}
