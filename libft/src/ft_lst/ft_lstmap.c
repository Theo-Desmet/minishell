/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:01:13 by bbordere          #+#    #+#             */
/*   Updated: 2021/12/01 11:56:48 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*m;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	m = NULL;
	while (lst)
	{
		temp = ft_lstnew((*f)(lst -> content));
		if (!temp)
		{
			ft_lstclear(&m, del);
			return (NULL);
		}
		ft_lstadd_back(&m, temp);
		lst = lst -> next;
	}
	return (m);
}
