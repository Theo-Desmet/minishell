/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:44:30 by tdesmet           #+#    #+#             */
/*   Updated: 2021/11/29 15:07:52 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*ptr;
	char	*ptr2;

	i = 0;
	ptr = (char *) dest;
	ptr2 = (char *) src;
	if (ptr > ptr2)
	{	
		while (n > 0)
		{
			n--;
			ptr[n] = ptr2[n];
		}
	}
	else
	{
		while (i < n)
		{
			ptr[i] = ptr2[i];
			i++;
		}
	}
	return (dest);
}
/*
int main()
{
	char str1[7] = "aabbcc";

	printf( "The string: %s\n", str1 );
	ft_memmove( str1 + 2, str1, 4 );
	printf( "New string: %s\n", str1 );
}*/
