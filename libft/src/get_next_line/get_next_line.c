/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:53:05 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/31 11:31:43 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_len(char *str, int start)
{
	int	i;

	i = start;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i - start);
}

int	mem_empty(char *memory)
{
	while (*memory)
		if (*(memory++) != 127)
			return (0);
	return (1);
}

char	*get_memory(int fd, int *bytes, char *memory)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	*tmp = '\0';
	while (!ft_strchr(tmp, '\n') && *bytes)
	{
		*bytes = read(fd, tmp, BUFFER_SIZE);
		if (*bytes < 0)
		{
			free(tmp);
			free(memory);
			return (NULL);
		}
		if (!*bytes && !*tmp)
			break ;
		tmp[*bytes] = '\0';
		memory = ft_strjoin1(memory, tmp);
	}
	free(tmp);
	return (memory);
}

char	*fill_line(char *memory)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (memory && memory[i] == 127)
		i++;
	line = malloc(sizeof(char) * (line_len(memory, i) + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (memory[i] && memory[i] != '\n')
	{
		line[j++] = memory[i];
		memory[i++] = 127;
	}
	if (memory[i] == '\n')
	{
		line[j++] = '\n';
		memory[i++] = 127;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	int			bytes;
	char		*line;
	static char	*memory;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	bytes = 1;
	memory = get_memory(fd, &bytes, memory);
	if (!memory)
		return (NULL);
	else if (!bytes && !*memory)
	{
		free(memory);
		return (NULL);
	}
	line = fill_line(memory);
	if (mem_empty(memory))
	{
		free(memory);
		memory = NULL;
	}
	return (line);
}
