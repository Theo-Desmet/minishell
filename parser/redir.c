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

void	ft_rd_in(t_data *data, char *arg, int i)
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
	if (i == 0)
		data->fd_in = newfd;
	else
		data->pipes[i - 1][0] = newfd;
}

void	ft_rd_out(t_data *data, char *arg, int i)
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
	if (i == data->nb_pipes)
		data->fd_out = newfd;
	else
		data->pipes[i][1] = newfd;
}

void	ft_rd_append(t_data *data, char *arg, int i)
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
	if (i == data->nb_pipes)
		data->fd_out = newfd;
	else
		data->pipes[i][1] = newfd;
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

	if (!access(cmd, X_OK|F_OK) && (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1)))
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

void	ft_get_cmd(char **command)
{
	ssize_t	i;
	ssize_t	j;
	size_t	len;

	i = -1;
	if (!command || !*command)
		return ;
	while (command[++i])
	{
		if (ft_issep(command[i][0]))
		{
			ft_memmove(command[i], &command[i][1], ft_strlen(command[i]));
			command[i][ft_strlen(command[i]) - 1] = '\0';
		}
	}
}

void	ft_exec(t_list **env, char *arg)
{
	char	**command;
	char	*path;

	command = ft_lexer(arg);
	ft_get_cmd(command);
	if (!command)
		ft_free_command_norme(arg);
	if (!*command)
	{
		ft_free_tab((void **)command);
		exit(EXIT_SUCCESS);
	}
	free(arg);
	path = ft_search_path(env, command[0]);
	if (!path)
	{
		ft_command_not_found(command[0]);
		ft_free_tab((void **)command);
		exit(127);
	}
	if (execve(path, command, ft_lst_to_tab(env)))
	{
		ft_command_not_found(command[0]);
		ft_free_tab((void **)command);
		// free(path);
		exit(127);
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

void	ft_find_heredoc(t_data *data, t_token **args)
{
	size_t	i;
	size_t	nb_heredoc;

	i = 0;
	nb_heredoc = 0;
	while (args[i])
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

void	ft_redirection(t_data *data, t_token **args, int index)
{
	int	i;

	i = 0;
	while (args[i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == R_IN)
			ft_rd_in(data, args[++i]->val, index);
		if (args[i]->type == R_OUT)
			ft_rd_out(data, args[++i]->val, index);
		if (args[i]->type == R_APPEND)
			ft_rd_append(data, args[++i]->val, index);
		i++;
	}
}

int		ft_isredir(t_token *token)
{
	return (token->type == R_APPEND || token->type == R_HERE_DOC || token->type == R_IN|| token->type == R_OUT
		|| token->type == OUT_A_FILE || token->type == OUT_FILE || token->type == IN_FILE || token->type == DELIMITER);
}

char	*ft_join_word(t_token **args)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = NULL;
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
	if (cmd[ft_strlen(cmd) - 1] == ' ')
		cmd[ft_strlen(cmd) - 1] = '\0';
	return (cmd);
}

char	*ft_check_last_heredoc(t_data *data, t_token **args)
{
	int		i;
	int		cnth;
	int		cnti;
	char	*name;

	i = 0;
	cnth = -1;
	cnti = -1;
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
	if (cnth > cnti)
		return (name);
	else
		return (free(name), NULL);
	// 	ft_rd_in(data, name, index);
	// free(name);
}
