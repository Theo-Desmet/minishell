/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:45:03 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/08 14:50:51 by tdesmet          ###   ########.fr       */
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

char	*ft_init_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	char	*cwd;

	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		return (NULL);
	data->pwd = ft_strjoin(cwd, "\n");
	return (data->pwd);
}

t_data	*ft_init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = ft_init_env(data->env, envp);
	if (!data->env)
		return (NULL);
	data->wd = ft_init_wd(data->wd);
	data->pwd = ft_init_pwd(data);
	if (!data->pwd || !data->wd)
		return (NULL);
	data->fd_in = -1;
	data->fd_out = -1;
	data->rtn_val = 0;
	data->nb_heredoc = 0;
	data->nb_pipes = 0;
	data->act_heredoc = -1;
	data->childs = NULL;
	data->pipes = NULL;
	data->lexer = ft_init_lexer();
	if (!data->lexer)
		return (NULL);
	return (data);
}
