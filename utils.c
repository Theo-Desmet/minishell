/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:46:47 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/01 18:48:06 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (ft_free_tab((void **)res));
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
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
