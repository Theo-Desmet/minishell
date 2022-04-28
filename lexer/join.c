/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:08:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/28 11:47:10 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_islimit(int type)
{
	return (type == PIPE || type == D_PIPE || type == D_AND
		|| type == I_PAR || type == O_PAR || type == R_IN || type == R_OUT
		|| type == R_HERE_DOC || type == R_APPEND || type == OUT_A_FILE
		|| type == OUT_FILE || type == IN_FILE || type == DELIMITER);
}

size_t	ft_count_join(t_token **tokens)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (tokens[i])
	{
		if (tokens[i] && !ft_islimit(tokens[i]->type))
			while (tokens[i] && !ft_islimit(tokens[i]->type))
				i++;
		else
			i++;
		nb++;
	}
	return (nb);
}

char	**ft_regroup_tokens(t_token **tokens, size_t *i, size_t *j, char **res)
{
	char	*temp;

	temp = NULL;
	if (tokens[*i] && !ft_islimit(tokens[*i]->type))
	{
		while (tokens[*i] && !ft_islimit(tokens[*i]->type))
			temp = ft_strjoin(ft_strjoin(temp, tokens[(*i)++]->val), " ");
		if (temp[ft_strlen(temp) - 1] == ' ')
			temp[ft_strlen(temp) - 1] = '\0';
		res[(*j)++] = ft_strdup(temp);
		free(temp);
	}
	else
		res[(*j)++] = ft_strdup(tokens[(*i)++]->val);
	return (res);
}

char	**ft_join(t_token **tokens)
{
	size_t	nb;
	size_t	i;
	size_t	j;
	char	**res;
	char	*temp;

	nb = ft_count_join(tokens);
	res = malloc(sizeof(char *) * (nb + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (j < nb)
		ft_regroup_tokens(tokens, &i, &j, res);
	res[j] = NULL;
	return (res);
}

void	ft_skip_sep(char *str, size_t *i)
{
	char	sep;

	sep = str[*i];
	while (str[*i] && str[*i] != sep)
		(*i)++;
}
