/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:39:26 by bbordere          #+#    #+#             */
/*   Updated: 2021/12/01 11:41:18 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*m;
	t_list	*temp;

	m = *lst;
	if (lst && del)
	{
		while (m)
		{
			temp = m -> next;
			ft_lstdelone(m, del);
			m = temp;
		}
		*lst = NULL;
	}
}
