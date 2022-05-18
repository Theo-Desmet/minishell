/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:46:39 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/17 21:48:23 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_check_here_doc(t_token **tokens, size_t i)
{
	if (i == ft_tab_size(tokens) - 1)
		return (0);
	return (tokens[i + 1]->type == WORD || tokens[i + 1]->type == VAR
		|| tokens[i + 1]->type == IN_FILE || tokens[i + 1]->type == DELIMITER
		|| !tokens[i + 1]);
}

int	ft_in_quotes(char *str, size_t *i, char *quote)
{
	int		in_quote;
	char	sep;

	in_quote = 0;
	if (str[(*i)] && ft_issep(str[(*i)]))
	{
		in_quote = 1;
		sep = str[(*i)++];
		while (str[(*i)] && str[(*i)] != sep)
			(*i)++;
		if (str[(*i)] == sep)
		{
			in_quote = 0;
			(*i)++;
		}
		if (!str[(*i)] && in_quote)
			return (*quote = sep, 0);
	}
	else
		(*i)++;
	return (1);
}

int	ft_check_quotes(t_token	*token, char *quote)
{
	size_t	i;

	i = 0;
	while (token->val[i] && !ft_issep(token->val[i]))
			i++;
	while (token->val[i])
		if (!ft_in_quotes(token->val, &i, quote))
			return (0);
	return (1);
}

int	ft_check_grammar(t_token **tokens)
{
	ssize_t	i;
	char	quote;

	i = -1;
	while (tokens[++i])
	{
		if (ft_isop(tokens[i]->type))
		{
			if (!ft_check_op(tokens, i))
				return (printf("%s'%s'\n", ERROR_MSG, tokens[i]->val), 0);
		}
		if (tokens[i]->type == R_HERE_DOC || tokens[i]->type == R_IN)
		{
			if (!ft_check_here_doc(tokens, i))
				return (printf("%s'%s'\n", ERROR_MSG, tokens[i]->val), 0);
		}
		if (tokens[i]->type == S_QUOTE || tokens[i]->type == D_QUOTE)
		{
			if (!ft_check_quotes(tokens[i], &quote))
				return (printf("minishell: unexpected EOF while	looking for matching \'%c\'\n", quote), 0);
		}
	}
	return (1);
}
