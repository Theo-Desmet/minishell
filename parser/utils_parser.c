/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:21:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/29 12:32:17 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isop(int type)
{
	return (type == R_OUT || type == R_APPEND
		|| type == PIPE || type == D_AND || type == D_PIPE);
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
		|| type == WILDCARD);
}

int	ft_isredir(t_token *token)
{
	return (token->type == R_APPEND || token->type == R_HERE_DOC
		|| token->type == R_IN || token->type == R_OUT
		|| token->type == OUT_A_FILE || token->type == OUT_FILE
		|| token->type == IN_FILE || token->type == DELIMITER);
}

int	ft_check_op(t_token **tokens, size_t i)
{
	if (i == 0 && tokens[i + 1])
		return (1);
	else if (i == ft_tab_size(tokens) - 1)
		return (0);
	else if (tokens[i]->type == R_OUT)
		return (ft_isvalidtype(tokens[i - 1]->type)
			&& ft_isvalidtype(tokens[i + 1]->type));
	else if (tokens[i]->type == R_APPEND || tokens[i]->type == D_AND
		|| tokens[i]->type == D_PIPE)
		return (ft_isvalidtype(tokens[i + 1]->type));
	return (1);
}
