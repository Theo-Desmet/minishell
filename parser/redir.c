/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:39:16 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/26 19:39:16 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**ft_lst_to_tab(t_list **lst);

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
			return (command);
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
	if (!access(cmd, 0))
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
	ft_free_tab((void **)paths);
	if (!command)
		return (NULL);
	return (command);
}

void	ft_command_not_found(char *arg)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_free_command_norme(char *arg)
{
	ft_command_not_found(arg);
	free(arg);
	exit(EXIT_FAILURE);
}

void	ft_exec(t_list **env, char *arg)
{
	char	**command;
	char	**envp;
	char	*path;

	command = ft_lexer(arg);
	if (!command)
		ft_free_command_norme(arg);
	free(arg);
	path = ft_search_path(env, command[0]);
	if (!path)
	{
		ft_command_not_found(command[0]);
		ft_free_tab((void **)command);
		exit(EXIT_FAILURE);
	}
	if (execve(path, command, ft_lst_to_tab(env)))
	{
		ft_command_not_found(command[0]);
		ft_free_tab((void **)command);
		free(path);
		exit(EXIT_FAILURE);
	}
	ft_free_tab((void **)command);
}

void	ft_here_doc(char *limiter, char *line, int fd, int len)
{
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(0);
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

void	ft_get_doc(char *limiter, int nb_heredoc)
{
	char	*line;
	size_t	len;
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
	int		i;
	char	*cmd;

	i = 0;
	cmd = malloc(sizeof(char));
	*cmd = 0;
	while (args[i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == WORD)
		{
			cmd = ft_strjoin(cmd, args[i]->val);
			cmd = ft_strjoin(cmd, " ");
		}
		i++;
	}
	if (!cmd || !(*cmd))
		return (NULL);
	return (cmd);
}

void	ft_check_last_heredoc(t_data *data, t_token **args)
{
	int		i;
	int		cnth;
	int		cnti;
	char	*name;

	i = 0;
	cnth = 0;
	cnti = 0;
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

void	ft_glhf(t_data *data, t_token **args, t_list **env)
{
	char	*cmd;

	ft_redirection(data, args);
	ft_check_last_heredoc(data, args);
	cmd = ft_join_word(args, env);
	ft_exec(env, cmd);
}

void	ft_fork(t_data *data, t_token **args, t_list **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!args || !(*args)) // !args[1]
		exit(EXIT_FAILURE);
	if (!pid)
		ft_glhf(data, args, env);
	else
		waitpid(pid, NULL, 0);
}


void	ft_pipe(t_data *data, t_token **args, t_list **env, int in)
{
	char	*cmd;
	int		pid;
	int		fd[2];

	if (pipe(fd) < 0)
		return ;
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!args || !(*args)) // !args[1]
		exit(EXIT_FAILURE);
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], data->fd_out);
		if (in == data->fd_in)
			exit(EXIT_FAILURE);
		ft_glhf(data, args, env);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], data->fd_in);
		close(fd[0]);
	}
	if (in != data->fd_out)
		close(in);
}

int	ft_check_isapipe(t_token **args, int *i)
{
	while (args[*i] && (args[*i]->type != D_PIPE || args[*i]->type != D_AND))
	{
		(*i)++;
		if (args[*i] && args[*i]->type == PIPE)
			return (1);
	}
	return (0);
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
		if (!args[i] || (args[i]
				&& (args[i]->type == D_PIPE && data->rtn_val != 0))
			|| (args[i] && (args[i]->type == D_AND && data->rtn_val == 0)))
			ft_fork(data, &args[j], env);
		if (args[i] && args[i]->type == PIPE)
		{
			ft_pipe(data, &args[j], env, data->fd_in);
			while (ft_check_isapipe(args, &i))
				ft_pipe(data, &args[i++], env, data->fd_out);
			ft_fork(data, &args[j], env);
		}
		if (args[i])
			i++;
		j = i;
	}
}