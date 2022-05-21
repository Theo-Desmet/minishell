/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:51:45 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/20 14:49:27 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list **env)
{
	t_list	*temp;
	int		i;

	if (!env || !(*env))
		return (0);
	temp = *env;
	while (temp)
	{
		i = 0;
		while (((char *)temp->content)[i])
		{
			if (((char *)temp->content)[i] == '=')
			{
				ft_printf("%s\n",temp->content);
				break;
			}
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
