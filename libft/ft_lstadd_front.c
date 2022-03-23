/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:33:08 by tdesmet           #+#    #+#             */
/*   Updated: 2021/12/01 14:41:04 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new -> next = *alst;
		*alst = new;
	}
}
/*
int main()
{
	t_list * l =  NULL;
	ft_lstadd_front(&l, ft_lstnew((void*)1));
}*/
