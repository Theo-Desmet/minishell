/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:58:05 by tdesmet           #+#    #+#             */
/*   Updated: 2022/01/20 08:46:43 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*mail;

	mail = NULL;
	if (!alst)
		return ;
	if (!(*alst))
		*alst = new;
	else
	{
		mail = ft_lstlast(*(alst));
		mail -> next = new;
	}
}
