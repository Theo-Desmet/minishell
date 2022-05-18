/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:33:46 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/19 21:33:46 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

size_t	ft_count_vars(char *str)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && (ft_is_valid_var_char(str[i + 1]) || str[i + 1] == '?'))
		{
			while (str[i] && (ft_is_valid_var_char(str[i]) || str[i] == '?'))
			{
				if (i == 1 && ft_isdigit(str[i + 1]))
					break;
				i++;
			}
			nb++;
		}
		i++;
	}
	return (nb);
}

size_t	ft_len_vars(char *str, size_t i)
{
	size_t	size;

	i++;
	size = 0;
	while (str[i - 1] && str[i] && (ft_is_valid_var_char(str[i]) || (str[i] == '?' && str[i - 1] == '$')))
	{
		if (str[i] == '?')
			return (2);
		i++;
		size++;
	}
	return (size + 1);
}

char	*ft_charjoin(char *str, char c)
{
	size_t	len;
	char	*res;

	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	ft_memcpy(res, str, len);
	res[len] = c;
	res[len + 1] = '\0';
	if (str)
		free(str);
	return (res);
}

void	ft_init_temp(t_temp *temp, char **vars, char *str, t_list **env)
{
	temp->vars = vars;
	temp->str = str;
	temp->env = env;
	temp->i = 0;
	temp->j = 0;
}
