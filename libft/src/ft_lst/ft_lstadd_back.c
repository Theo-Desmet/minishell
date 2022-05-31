/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:14:33 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/25 15:20:52 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{	
	t_list	*p;

	if (!(*alst))
		*alst = new;
	else
	{
		p = ft_lstlast(*alst);
		p -> next = new;
	}
}
