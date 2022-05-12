/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:35:46 by bbordere          #+#    #+#             */
/*   Updated: 2021/11/25 09:57:58 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*b1;
	unsigned char	*b2;

	b1 = (unsigned char *) s1;
	b2 = (unsigned char *) s2;
	while (n-- > 0)
	{
		if (*b1 != *b2)
			return (*b1 - *b2);
		b1++;
		b2++;
	}
	return (0);
}
