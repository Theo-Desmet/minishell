/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 08:09:34 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/20 17:01:00 by tdesmet          ###   ########.fr       */
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
		ft_putstr_fd(": Not such file or directory\n", 2);// a changer
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
		ft_putstr_fd(": Not such file or directory\n", 2);// a changer
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
		ft_putstr_fd(": Not such file or directory\n", 2);// a changer
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

void    ft_get_doc(char *limiter, int nb_heredoc)
{
	char    *line;
	size_t    len;
	int		fd;
	char	*name;

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

void	ft_find_heredoc(t_data *data, t_token **args)
{
	size_t	i;
	size_t	nb_heredoc;

	i = 0;
	nb_heredoc = 0;
	while (args[i] && args[i]->type != PIPE)
	{
		if (args[i]->type == R_HERE_DOC)
		{
			ft_get_doc(args[++i]->val, nb_heredoc);
			nb_heredoc++;
		}
		i++;
	}
	data->nb_heredoc = nb_heredoc;
}

void	ft_redirection(t_data *data, t_token **args)
{
	int	i;

	i = 0;
	while (args[i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
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

char	*ft_join_word(t_token **args, t_list **env)
{
	int	i;
	char	*cmd;

	i = 0;
	cmd = malloc(sizeof(char));
	*cmd = 0;
	while (args[i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == WORD)
		{
			cmd = ft_strjoin_free(cmd, args[i]->val);
			cmd = ft_strjoin_free(cmd, " ");
		}
		i++;
	}
	if (!cmd || !(*cmd))
		return (NULL);
	return	(cmd);
}

void	ft_check_last_heredoc(t_data *data, t_token **args)
{
	int	i;
	int	cnth;
	int	cnti;
	char	*name;

	i = 0;
	cnth = 0;
	name = NULL;
	while (args[i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == R_HERE_DOC)
		{
			data->act_heredoc++;
			cnth = i;
		}
		if (args[i]->type == R_IN)
			cnti = i;
		i++;
	}
	name = ft_strjoin("/tmp/minishell", ft_itoa(data->act_heredoc));
	if (cnth > cnti && cnth != 0)
		ft_rd_in(data, name);
	free(name);
}

void	ft_fork(t_data *data, t_token **args, t_list **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!args || !(*args) || !args[1])
		exit(EXIT_FAILURE);
	if (!pid)
	{
		ft_glhf(data, args, env);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_glhf(t_data *data, t_token **args, t_list **env)
{
	char	*cmd;

	ft_redirection(data, args);
	ft_check_last_heredoc(data, args);
	cmd = ft_join_word(args, env); 
	ft_exec(env, cmd);
	free(cmd);
}

void	ft_pipe(t_data *data, t_token **args, t_list **env)
{
	char	*cmd;
	int	pid;
	int	fd[2];

	fd[0] = data->fd_in;
	fd[1] = data->fd_out;
	if (pipe(fd) < 0)
		return ;
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!args || !(*args) || !args[1])
		exit(EXIT_FAILURE);
	if (!pid)

	else
		waitpid(pid, NULL, 0);
}

void	ft_check_separator(t_data *data, t_token **args, t_list **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_find_heredoc(data, args);
	while (args[i])
	{
		while (args[i] && args[i]->type != PIPE
				&& args[i]->type != D_PIPE && args[i]->type != D_AND)
			i++;
		if (!args[i] || (args[i] && (args[i]->type == D_PIPE && data->rtn_val != 0))
				|| (args[i] && (args[i]->type == D_AND && data->rtn_val == 0)))
			ft_fork(data, &args[j], env);
		if (args[i] && args[i]->type == PIPE)
		{
			ft_pipe(data, &args[j], env);
			while (args[i] && args[i]->type != PIPE
					&& args[i]->type != D_PIPE && args[i]->type != D_AND)
			i++;
		}
		i++;
		j = i;
	}
}
