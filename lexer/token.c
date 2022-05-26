/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:08:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/25 11:08:42 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_skip_quotes(char *val, ssize_t *i)
{
	char	sep;

	sep = val[*i];
	(*i)++;
	while (val[*i] && val[*i] != sep)
		(*i)++;
}

int	ft_iswildcard(char *val)
{
	ssize_t	i;

	i = -1;
	while (val[++i])
	{
		if (val[i] && ft_issep(val[i]))
			ft_skip_quotes(val, &i);
		if (val[i] && val[i] == '*')
			return (1);
	}
	return (0);
}

int	ft_init_op(t_token *token, char *val)
{
	if (!ft_strcmp(val, "<") && ft_strlen(val) == 1)
		token->type = R_IN;
	else if (!ft_strcmp(val, "<<") && ft_strlen(val) == 2)
		token->type = R_HERE_DOC;
	else if (!ft_strcmp(val, ">") && ft_strlen(val) == 1)
		token->type = R_OUT;
	else if (!ft_strcmp(val, ">>") && ft_strlen(val) == 2)
		token->type = R_APPEND;
	else if (!ft_strcmp(val, "&"))
		token->type = WORD;
	else if (!ft_strcmp(val, "&&") && ft_strlen(val) == 2)
		token->type = D_AND;
	else if (ft_strstr(val, "*") && ft_iswildcard(val))
		token->type = WILDCARD;
	else if (ft_strstr(val, "\""))
		token->type = D_QUOTE;
	else if (ft_strstr(val, "\'"))
		token->type = S_QUOTE;
	else if (ft_strstr(val, "$") && !ft_isfulldollar(val))
		token->type = VAR;
	return (token->type == T_NULL);
}

t_token	*ft_init_token(char *val)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->val = ft_strdup(val);
	token->type = T_NULL;
	if (!ft_init_op(token, val))
		return (token);
	if (!ft_strcmp(val, "|"))
		token->type = PIPE;
	else if (!ft_strcmp(val, "||"))
		token->type = D_PIPE;
	else if (!ft_strcmp(val, "("))
		token->type = I_PAR;
	else if (!ft_strcmp(val, ")"))
		token->type = O_PAR;
	else
		token->type = WORD;
	return (token);
}

t_token	**ft_tokenize(char **tab)
{
	t_token	**res;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (tab[size])
		size++;
	res = malloc(sizeof(t_token *) * (size + 1));
	if (!res)
		return (NULL);
	while (tab[i])
	{
		res[i] = ft_init_token(tab[i]);
		i++;
	}
	res[size] = NULL;
	return (res);
}
