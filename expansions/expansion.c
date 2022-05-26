/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:45:38 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 12:23:01 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	**ft_init_expand(char **res, char *str, t_temp *temp, t_list	**env)
{
	char	**vars;

	vars = ft_extract_var(str);
	if (!vars)
		return (NULL);
	*res = NULL;
	ft_init_temp(temp, vars, str, env);
	return (vars);
}

char	*ft_expand_str(t_list **env, char *str)
{
	char	**vars;
	char	*res;
	t_temp	temp;

	vars = ft_init_expand(&res, str, &temp, env);
	if (!vars)
		return (NULL);
	while (str[temp.i])
	{
		if (str[temp.i] == '\"')
			res = ft_str_var(res, &temp);
		else if (str[temp.i] == '\'')
			res = ft_copy_quotes(res, &temp);
		else if (str[temp.i + 1] && str[temp.i] == '$'
			&& (ft_valid_var_char(str[temp.i + 1]) || str[temp.i + 1] == '?'))
			res = ft_var(res, &temp);
		else if (str[temp.i] == '$' && ft_issep(str[temp.i + 1]))
			temp.i++;
		else
			res = ft_charjoin(res, str[temp.i++]);
	}
	res = ft_frame_str(res, ft_get_inverted_quote(res));
	ft_free((void **)temp.vars);
	free(temp.str);
	return (res);
}

char	*ft_not_wd(char *val, char **temp)
{
	char	*res;

	ft_free_tab((void **)temp);
	res = ft_strdup(val);
	free(val);
	return (res);
}

char	*ft_expand_wildcard(t_list **wd, char *val, t_list **env)
{
	char	*res;
	char	**temp;
	size_t	i;

	i = 0;
	res = NULL;
	val = ft_expand_str(env, val);
	if (ft_issep(*val))
	{
		ft_memmove(val, &val[1], ft_strlen(val));
		val[ft_strlen(val) - 1] = '\0';
	}
	ft_wildcard(wd, val);
	temp = ft_lst_to_tab(wd);
	if (!temp)
		return (NULL);
	if (!*temp)
		return (ft_not_wd(val, temp));
	free(val);
	while (temp[i])
		res = ft_strjoin1(ft_strjoin1(res, temp[i++]), " ");
	ft_free_tab((void **)temp);
	ft_lstclear(wd, free);
	return (res);
}

void	ft_expand(t_token **tokens, t_list **env, t_list **wd)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == VAR || tokens[i]->type == D_QUOTE
			|| tokens[i]->type == IN_FILE || tokens[i]->type == OUT_A_FILE
			|| tokens[i]->type == OUT_FILE || tokens[i]->type == S_QUOTE)
			tokens[i]->val = ft_expand_str(env, tokens[i]->val);
		else if (tokens[i]->type == WILDCARD)
			tokens[i]->val = ft_expand_wildcard(wd, tokens[i]->val, env);
		i++;
	}	
}
