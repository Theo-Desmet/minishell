/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:56:30 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/22 08:16:53 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 10000

void	*free_mem(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*free_line(char *line, char *mem)
{
	char	*newline;
	int		lline;
	int		lmem;

	if (!line || !mem)
		return (free_line(line, NULL));
	newline = NULL;
	lline = ft_strlen(line);
	lmem = ft_strlen(mem);
	newline = malloc(sizeof(char) * (lline - lmem + 1));
	if (!newline)
		return (NULL);
	ft_memcpy(newline, line + lmem, lline - lmem + 1);
	free(line);
	return (newline);
}

char	*read_line(char *line, int fd)
{
	int		ret;
	char	*buf;

	ret = 1;
	buf = malloc(sizeof(char *) * BUFFER_SIZE +1);
	if (!buf)
		return (0);
	*buf = 0;
	while (!ft_strchr(buf, '\n') && ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (free_mem(buf, line));
		buf[ret] = '\0';
		if (ret)
			line = ft_strjoin_free(line, buf);
	}
	free(buf);
	if (!ret && !line)
		return (NULL);
	if (!ret && !*line)
		return (free_mem(line, NULL));
	return (line);
}

char	*get_line(char *line)
{
	int		i;
	char	*mem;

	i = 0;
	if (!line || *line == 0 || !*line)
		return (NULL);
	mem = ft_strdup(line);
	while (mem[i] != '\n' && mem[i] != '\0')
		i++;
	mem[i + 1] = 0;
	return (mem);
}

char	*ft_get_next_line(int fd)
{
	static char	*line;
	char		*mem;
	int			i;

	i = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!line)
		line = read_line(line, fd);
	if (line)
	{
		while (line[i] != '\n' && line[i] != '\0')
			i++;
		if (line[i] != '\n')
			line = read_line(line, fd);
		mem = get_line(line);
	}
	if (!line)
		return (NULL);
	line = free_line(line, mem);
	return (mem);
}
