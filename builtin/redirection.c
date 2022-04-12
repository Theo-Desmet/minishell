/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 08:09:34 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/12 14:47:04 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_rd_in(char *arg, int fd)
{
	int	newfd;

	newfd = open(arg, O_RDONLY);
	if (newfd < 0)
	{
		perror("open");
		return (fd);
	}
	if (dup2(newfd, fd) == -1)
		return (fd);
	return (newfd);
}

void	ft_rd_out(char *arg)
{
	int	newfd;

	newfd = open(arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (newfd < 0)
	{
		perror("open");
		return ;
	}
	if (dup2(newfd, STDOUT_FILENO) == -1)
		return ;
}

void	ft_rd_append(char *arg)
{
	int	newfd;

	newfd = open(arg, O_CREAT | O_RDWR, 0664);
	if (newfd < 0)
	{
		perror("open");
		return ;
	}
	if (dup2(newfd, STDOUT_FILENO) == -1)
		return ;
}
/*
int    ft_isbuiltin(char *val)
{
	char    **tab;

	tab = ft_lexer(val);
	if (!tab || !*tab)
		return (0);
	if (ft_strnstr(tab[0], "echo", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "cd", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "pwd", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "export", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "unset", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "env", ft_strlen(tab[0]))
		|| ft_strnstr(tab[0], "exit", ft_strlen(tab[0])))
	{
		ft_free((void **)tab);
		return (1);
	}
	ft_free((void **)tab);
	return (0);
}*/

void	ft_free(void **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void    ft_get_doc(char *limiter, int *fd)
{
	char    *line;
	size_t    len;

	close(fd[0]);
	len = ft_strlen(limiter);
	while (1)
	{
		write(0, "pipex heredoc> ", 15);
		line = ft_get_next_line(0);
		if (!line)
			break ;
	if (line[len] == '\n' && !ft_strncmp(line, limiter, len))
	{
		free(line);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	write(fd[1], line, ft_strlen(line));
	free(line);
	}
}

void	ft_redirection(t_token **args, int fd)
{
	int	i;

	if (!args || !(*args) || !args[1])
		return ;
	i = 0;
	while (args[i])
	{
		if (args[i]->type == R_IN)
			fd = ft_rd_in(args[++i]->val, fd);
		else if (args[i]->type == R_HERE_DOC)
			return	;
		else if (args[i]->type == R_OUT)
			ft_rd_out(args[++i]->val);
		else if (args[i]->type == R_APPEND)
			ft_rd_append(args[++i]->val);
		else if (args[i]->type == CMD)
			printf("coucou");
			
		i++;
	}
}
