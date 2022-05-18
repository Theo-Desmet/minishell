/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:21:42 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/17 21:49:12 by bbordere         ###   ########.fr       */
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
		|| type == VAR || type == OUT_FILE || type == OUT_A_FILE || type == WILDCARD);
}

int	ft_check_op(t_token **tokens, size_t i)
{
	if (i == 0 || i == ft_tab_size(tokens) - 1)
		return (0);
	else if (tokens[i]->type == R_OUT)
		return (ft_isvalidtype(tokens[i - 1]->type)
			&& ft_isvalidtype(tokens[i + 1]->type));
	else if (tokens[i]->type == R_APPEND)
		return (ft_isvalidtype(tokens[i + 1]->type));
	return (1);
}
