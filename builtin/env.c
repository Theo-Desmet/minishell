/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:51:45 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/25 15:22:09 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_list **env)
{
	t_list	*temp;

	if (!env)
		return (0);
	temp = *env;
	while (temp && temp->next)
	{
		ft_putstr(temp->content);
		ft_putchar('\n');
		temp = temp->next;
	}
	return (1);
}
