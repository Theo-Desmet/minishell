/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:28:52 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/01 18:51:28 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_global	g_global;

void	ft_update_shlvl(t_list **env)
{
	t_list	*temp;
	char	*str;
	void	*addr;

	if (!*env)
	{
		ft_export(env, ft_split("export SHLVL=1", ' '));
		return ;
	}
	temp = *env;
	while (temp)
	{
		if (ft_strnstr((char *)(temp->content), "SHLVL=", 6))
		{
			str = ft_getenv(env, "SHLVL");
			addr = temp->content;
			temp->content = ft_strjoin2("SHLVL=", ft_itoa(ft_atoi(str) + 1));
			free(addr);
			return ;
		}
		temp = temp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	ft_sig_init();
	data = ft_init_data(env);
	ft_update_shlvl(data->env);
	while (1)
	{
		g_global.prompt = ft_prompt(data->env);
		data->lexer->input = readline(g_global.prompt);
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
			if (g_global.rtn_val == 139)
				write(2, "Segmentation fault\n", 19);
			if (g_global.rtn_val == 134)
				write(2, "Abort\n", 6);
		}
		ft_free_lexer(data);
		free(g_global.prompt);
	}
	ft_free_data(data);
	printf("exit\n");
	rl_clear_history();
	return (0);
}
