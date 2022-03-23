/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 08:37:01 by tdesmet           #+#    #+#             */
/*   Updated: 2021/12/01 15:36:28 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_cont;

	new_lst = NULL;
	new_cont = NULL;
	if (lst)
	{
		while (lst)
		{
			new_cont = ft_lstnew((*f)(lst -> content));
			if (!new_cont)
			{
				ft_lstclear(&new_lst, del);
				return (NULL);
			}
			ft_lstadd_back(&new_lst, new_cont);
			lst = lst -> next;
		}
	}
	return (new_lst);
}
