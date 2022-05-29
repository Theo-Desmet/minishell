/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:28:52 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/29 12:42:42 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**ft_init_env(t_list **env, char **envp)
{
	size_t	i;
	t_list	*temp;
	char	*value;

	env = malloc(sizeof(t_list));
	if (!env)
		return (NULL);
	*env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		ft_lstadd_back(env, ft_lstnew(envp[i]));
		i++;
	}
	temp = *env;
	while (temp)
	{
		value = temp->content;
		temp->content = ft_strdup(value);
		temp = temp->next;
	}
	return (env);
}

t_list	**ft_init_wd(t_list **wd)
{
	wd = malloc(sizeof(t_list));
	if (!wd)
		return (NULL);
	*wd = NULL;
	return (wd);
}

t_lexer	*ft_init_lexer(void)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = NULL;
	lexer->lexed = NULL;
	lexer->tokens = NULL;
	return (lexer);
}

t_data	*ft_init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);//modifier secu err dans main
	data->env = ft_init_env(data->env, envp);
	if (!data->env)
		return (NULL);
	data->wd = ft_init_wd(data->wd);
	if (!data->wd)
		return (NULL);
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	data->pwd = ft_strdup("");
	data->rtn_val = 0;
	data->nb_heredoc = 0;
	data->act_heredoc = -1;
	data->childs = NULL;
	data->pipes = NULL;
	data->lexer = ft_init_lexer();
	if (!data->lexer)
		return (NULL);
	return (data);
}

char	**ft_lst_to_tab(t_list **lst)
{
	t_list	*temp;
	char	**res;
	size_t	i;

	temp = *lst;
	res = malloc(sizeof(char *) * (ft_lstsize(temp) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (temp)
	{
		res[i] = ft_strdup(((char *)temp->content));
		if (!res[i])
			return (NULL);// FREE ALL
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}

void	ft_lstdel_all(t_list **lst)
{
	t_list	*temp;

	if (!lst)
		return ;
	temp = *lst;
	while (lst && *lst)
	{
		(*lst) = (*lst)->next;
		free(temp->content);
		free(temp);
		temp = *lst;
	}
	free(lst);
}

void	*ft_free_tokens(t_token **tokens)
{
	size_t	i;

	i = 0;
	if (!tokens)
		return (NULL);
	while (tokens[i])
	{
		free(tokens[i]->val);
		i++;
	}
	ft_free((void **)tokens);
	tokens = NULL;
	return (NULL);
}

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("%s {%d} |%p| -> ", ((t_token *)lst->content)->val,
			((t_token *)lst->content)->type, lst);
		lst = lst->next;
	}
	printf("NULL\n");
}

void	ft_update_files(t_token **tokens, size_t i)
{
	if (tokens[i - 1]->type == R_OUT)
		tokens[i]->type = OUT_FILE;
	else if (tokens[i - 1]->type == R_IN)
		tokens[i]->type = IN_FILE;
	else if (tokens[i - 1]->type == R_HERE_DOC)
		tokens[i]->type = DELIMITER;
	else if (tokens[i - 1]->type == R_APPEND)
		tokens[i]->type = OUT_A_FILE;
}

void	ft_update_type(t_token **tokens, int mode)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (mode == 1)
			if (tokens[i]->type == WILDCARD || tokens[i]->type == S_QUOTE
				|| tokens[i]->type == D_QUOTE || tokens[i]->type == VAR)
				tokens[i]->type = WORD;
		if (i != 0 && tokens[i - 1])
			ft_update_files(tokens, i);
		if (tokens[i]->type == OUT_A_FILE || tokens[i]->type == OUT_FILE
			||tokens[i]->type == IN_FILE || tokens[i]->type == DELIMITER)
		{
			if (tokens[i]->val[0] == '\'')
			{
				ft_memmove(tokens[i]->val, &tokens[i]->val[1],
					ft_strlen(tokens[i]->val));
				tokens[i]->val[ft_strlen(tokens[i]->val) - 1] = '\0';
			}
		}
		i++;
	}
}

char	*ft_prompt(t_list **env)
{
	char	*prompt;
	char	*pwd;
	char	*home;
	char	*temp;

	if (!*env)
		return (ft_strdup("minishell > "));
	pwd = ft_get_var(env, "PWD");
	if (!*pwd)
		return (free(pwd), ft_strdup("minishell > "));
	temp = pwd;
	pwd = ft_strrchr(pwd, '/') + 1;
	home = ft_get_var(env, "HOME");
	if (!*home)
		return (free(temp), free(home), ft_strdup("minishell > "));
	prompt = ft_strjoin2("\1\033[0;31m\2", ft_strjoin1(
				ft_charjoin(ft_get_var(env, "LOGNAME"), '@'),
				"minishell\1\033[0;37m:\033[0;33m\2"));
	if (ft_strstr(pwd, home))
		prompt = ft_strjoin1(prompt, ft_strjoin2("~", pwd + ft_strlen(home)));
	else
		prompt = ft_strjoin1(prompt, pwd);
	prompt = ft_strjoin1(prompt, "\1\033[0;37m\2$ ");
	free(home);
	free(temp);
	return (prompt);
}

void	handler_int(int sig)
{
	if (g_global.in_exec == 0)
	{
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			if (g_global.pid == 0)
				rl_redisplay();
			g_global.rtn_val = 130;
		}
		else if (sig == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b\n", 1);
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_global.rtn_val = 130;
		kill(g_global.pid, SIGINT);
	}
}

int	ft_sig_init(void)
{
	struct sigaction	sig;
	t_global			g_global;

	sig.sa_handler = &handler_int;
	sigemptyset(&sig.sa_mask);
	signal(SIGINT, &handler_int);
	signal(SIGABRT, &handler_int);
	signal(SIGSEGV, &handler_int);
	g_global.in_exec = 0;
	g_global.pid = -1;
	g_global.rtn_val = 0;
	return (1);
}

void	ft_free_lexer(t_data *data)
{
	if (data->lexer->lexed)
		data->lexer->lexed = ft_free_tab((void **)data->lexer->lexed);
	if (data->lexer->tokens)
		data->lexer->tokens = ft_free_tokens(data->lexer->tokens);
	if (data->lexer->input)
		free(data->lexer->input);
	data->lexer->input = NULL;
}

int	ft_get_cmd_line(t_data *data)
{
	data->lexer->lexed = ft_lexer(data->lexer->input);
	data->lexer->tokens = ft_tokenize(data->lexer->lexed);
	data->fd_in = dup(STDIN_FILENO);
	data->fd_out = dup(STDOUT_FILENO);
	if (!ft_check_grammar(data->lexer->tokens))
		return (ft_free_lexer(data), -1);
	ft_update_type(data->lexer->tokens, 0);
	ft_expand(data->lexer->tokens, data->env, data->wd);
	ft_free_tab((void **)data->lexer->lexed);
	data->lexer->lexed = ft_join(data->lexer->tokens);
	ft_free_tokens(data->lexer->tokens);
	data->lexer->tokens = ft_tokenize(data->lexer->lexed);
	ft_update_type(data->lexer->tokens, 1);
	return (0);
}

void	ft_free_data(t_data *data)
{
	if (data->pipes)
		ft_free_tab((void **)data->pipes);
	if (data->childs)
		free(data->childs);
	ft_lstdel_all(data->env);
	ft_lstdel_all(data->wd);
	if (data->lexer)
	{
		ft_free_lexer(data);
		free(data->lexer);
	}
	if (data->pwd)
		free(data->pwd);
	free(data);
	if (g_global.prompt)
		free(g_global.prompt);
}

t_global	g_global;

int	main(int ac, char **av, char **env)
{
	t_data *data;

	ft_sig_init();
	data = ft_init_data(env);
	while (1)
	{
		g_global.prompt = ft_prompt(data->env);
		data->lexer->input = readline(g_global.prompt);
		// input = readline("$> ");
		if (!data->lexer->input)
			break ;
		if (*(data->lexer->input))
		{
			g_global.in_exec = 1;
			add_history(data->lexer->input);
			if (ft_get_cmd_line(data) == -1)
			{
				g_global.in_exec = 0;
				free(g_global.prompt);
				continue ;
			}
			ft_pipeline(data, data->lexer->tokens);
			g_global.in_exec = 0;
		}
		ft_free_lexer(data);
		free(g_global.prompt);
	}
	ft_free_data(data);
	printf("exit\n");
	rl_clear_history();
	return (0);
}
