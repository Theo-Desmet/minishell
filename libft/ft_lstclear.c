/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 08:04:52 by tdesmet           #+#    #+#             */
/*   Updated: 2021/12/01 15:19:33 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_mail;

	next_mail = NULL;
	if (lst)
	{
		while (*lst)
		{
			next_mail = (*lst)-> next;
			ft_lstdelone(*lst, del);
			(*lst) = next_mail;
		}
	}
}
