/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:41:08 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/11 16:42:49 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quit(t_data *data, char *here_doc, int fork)
{
	ft_close(&data->fd_in, &data->fd_out);
	if (here_doc)
		free(here_doc);
	if (data)
		ft_free_data(data);
	if (fork)
		exit(EXIT_FAILURE);
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
		if (temp->content)
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

void	ft_free_data(t_data *data)
{
	if (data->env)
		ft_lstdel_all(data->env);
	if (data->pwd)
		ft_lstdel_all(data->wd);
	if (data->pwd)
		free(data->pwd);
	if (data->childs)
		free(data->childs);
	if (data->pipes)
	{
		ft_close_all(data);
		ft_free_tab((void **)data->pipes);
	}
	if (data->lexer)
	{
		ft_free_lexer(data);
		free(data->lexer);
	}
	free(data);
	if (g_global.prompt)
		free(g_global.prompt);
}
