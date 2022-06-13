/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:21:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/13 15:47:32 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isop(int type)
{
	return (type == PIPE || type == D_AND || type == D_PIPE);
}

size_t	ft_tab_size(t_token	**tokens)
{
	size_t	len;

	len = 0;
	while (tokens[len])
		len++;
	return (len);
}

int	ft_isvalidtype(int type)
{
	return (type == S_QUOTE || type == D_QUOTE || type == WORD || type == ARGS
		|| type == VAR || type == OUT_FILE || type == OUT_A_FILE
		|| type == WILDCARD || type == R_IN || type == R_APPEND
		|| type == R_OUT || type == R_HERE_DOC || type == PIPE);
}

int	ft_isredir(t_token *token)
{
	return (token->type == R_APPEND || token->type == R_HERE_DOC
		|| token->type == R_IN || token->type == R_OUT);
}

int	ft_check_op(t_token **tokens, size_t i)
{
	if (i == 0 || i == ft_tab_size(tokens) - 1 || !tokens[i + 1]
		|| !tokens[i - 1])
		return (0);
	if (ft_isredir(tokens[i - 1]) || ft_isop(tokens[i - 1]->type))
		return (0);
	return (1);
}
