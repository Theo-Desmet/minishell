/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:51:45 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/17 00:18:47 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
				ft_putstr(temp->content);
				ft_putchar('\n');
				break;
			}
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
