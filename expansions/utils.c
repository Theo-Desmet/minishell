/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:16:10 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/26 12:17:07 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*ft_copy_quotes(char *res, t_temp *temp)
{
	res = ft_strjoin(res, ft_get_str(&temp->str[(temp->i)++], 0));
	while (temp->str[temp->i] && temp->str[temp->i] != '\'')
		temp->i++;
	temp->i++;
	return (res);
}

char	*ft_frame_str(char *str, char c)
{
	char	*res;
	ssize_t	i;

	if (!str)
		return (ft_strdup("\"\""));
	if (!*str)
		return (str);
	res = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!res)
		return (NULL);
	i = -1;
	res[0] = c;
	while (str[++i])
		res[i + 1] = str[i];
	res[i++ + 1] = c;
	res[i + 1] = '\0';
	free(str);
	return (res);
}

char	ft_get_inverted_quote(char *str)
{
	char	quote;
	ssize_t	i;

	if (!str || !*str)
		return ('\"');
	if (*str == 127)
		return ('\'');
	i = -1;
	quote = 127;
	while (str[++i])
	{
		if (str[i] && ft_issep(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i])
				break ;
		}
	}
	if (quote == '\'')
		return ('\"');
	else
		return ('\'');
}
