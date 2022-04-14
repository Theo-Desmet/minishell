/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 08:09:34 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/14 15:59:58 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_rd_in(t_data *data, char *arg)
{
	int	newfd;

	newfd = open(arg, O_RDONLY);
	if (newfd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Not such file or directory", 2);// a changer
		exit(EXIT_FAILURE);
	}
	if (dup2(newfd, data->fd_in) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	ft_rd_out(t_data *data, char *arg)
{
	int	newfd;

	newfd = open(arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (newfd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Not such file or directory", 2);// a changer
		exit(EXIT_FAILURE);
	}
	if (dup2(newfd, data->fd_out) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	ft_rd_append(t_data *data, char *arg)
{
	int	newfd;

	newfd = open(arg, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (newfd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Not such file or directory", 2);// a changer
		exit(EXIT_FAILURE);
	}
	if (dup2(newfd, data->fd_out) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
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


char	*ft_check_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
		{
			return (command);
		}
		free(command);
		i++;
	}
	return (NULL);
}

char	*ft_search_path(t_list **env, char *cmd)
{
	char	**paths;
	char	*command;
	t_list	*temp;

	//check builtin
	if (access(cmd, 0) == 0)
		return (cmd);
	if (!env || !(*env))
		return (NULL);
	temp = *env;
	while (temp && temp->next && ft_strncmp("PATH=", temp->content, 5))
		temp = temp->next;
	if (!temp->next || ft_strncmp("PATH=", temp->content, 5))
		return (NULL);
	paths = ft_split(temp->content + 5, ':');
	command = ft_check_path(paths, cmd);
	ft_free_tab(paths);
	if (!command)
		return (NULL);
	return (command);
}

/*
char	**ft_get_all_arg(t_list **env, t_token **args, int *i)
{	
	int	j;
	int	k;
	char	**command;

	j = *i + 1;
	while (args && args[j] && args[j]->type == ARGS)
		j++;
	command = malloc(sizeof(char *) * (j - *i) + 1);
	if (!command)
		return (NULL);
	while (*i < j)
	{
		command[k] = malloc(sizeof(char) * (ft_strlen(args[*i]->val)) + 1);
		if (!command[k])
		{
			ft_free_tab(command);
			return (NULL);
		}
		command[k] = args[*i]->val;
		k++;
		(*i)++;
	}
	return (command);
}
*/
char **ft_lst_to_tab(t_list **lst)
{
	t_list	*temp; 
	char    **res;
	size_t    i;

	temp = *lst;
	res = malloc(sizeof(char *) * (ft_lstsize(temp) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (temp)
	{
		res[i] = ft_strdup((char *)temp->content);
		if (!res[i])
	    		return (NULL); // FREE ALL
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}

void	ft_exec(t_list **env, char *arg)
{
	char	**command;
	char	**envp;
	char	*path;

	command = ft_split(arg, ' ');
	if (!command)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(arg);
		exit(EXIT_FAILURE);
	}
	path = ft_search_path(env, command[0]);
	if (!path)
	{
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_tab(command);
		free(arg);
		exit(EXIT_FAILURE);
	}
	if (execve(path, command, ft_lst_to_tab(env)))
	{
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_tab(command);
		free(path);
		free(arg);
		exit(EXIT_FAILURE);
	}
	ft_free_tab(command);
}

void	ft_here_doc(char *limiter, char *line, int fd, int len)
{
	while (1)
	{
		write(0, "> ", 2);
		line = ft_get_next_line(0);
		if (!line)
		{
			if (close(fd))
				; //error close
			return ;
			//warning error
		}
		if (!ft_strncmp(line, limiter, len) && line[len] == '\n')
		{
			if (close(fd))
				; //error close
			free(line);
			return ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

void    ft_get_doc(char *limiter)
{
	char    *line;
	size_t    len;
	int		fd;

	fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (!fd)
		return ;
	len = ft_strlen(limiter);
	ft_here_doc(limiter, line, fd, len);
}

void	ft_find_heredoc(t_token **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (args[i]->type == R_HERE_DOC)
			ft_get_doc(args[++i]->val);
		i++;
	}
}

void	ft_redirection(t_data *data, t_token **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i]->type == R_IN)
			ft_rd_in(data, args[++i]->val);
		if (args[i]->type == R_OUT)
			ft_rd_out(data, args[++i]->val);
		if (args[i]->type == R_APPEND)
			ft_rd_append(data, args[++i]->val);
		i++;
	}
}

void	ft_join_word(t_token **args, t_list **env)
{
	int	i;
	char	*cmd;

	i = 0;
	cmd = malloc(sizeof(char));
	*cmd = 0;
	while (args[i])
	{
		if (args[i]->type == WORD)
		{
			cmd = ft_strjoin_free(cmd, args[i]->val);
			cmd = ft_strjoin_free(cmd, " ");
		}
		i++;
	}
	ft_exec(env, cmd);
}

void	ft_glhf(t_token **args, t_list **env, t_data *data)
{
	int	i;
	int	cnth;
	int	cnti;

	if (!args || !(*args) || !args[1])
		return ;
	ft_find_heredoc(args);
	ft_redirection(data, args);
	i = 0;
	while (args[i])
	{
		if (args[i]->type == R_HERE_DOC)
			cnth = i;
		if (args[i]->type == R_IN)
			cnti = i;
		i++;
	}
	if (cnth > cnti)
		ft_rd_in(data, "/tmp/minishell");
	ft_join_word(args, env);
}
