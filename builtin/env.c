/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:51:45 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/15 10:27:49 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_list **env)
{
	t_list	*temp;

	if (!env || !(*env))
		return (0);
	temp = *env;
	while (temp)
	{
		ft_putstr(temp->content, NULL);
		ft_putchar('\n', NULL);
		temp = temp->next;
	}
	return (1);
}
