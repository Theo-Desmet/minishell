/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:17:47 by bbordere          #+#    #+#             */
/*   Updated: 2021/12/02 11:41:42 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*dest;
	size_t			i;

	source = (unsigned char *) src;
	dest = (unsigned char *) dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (n == 0)
		return (dst);
	while (n--)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
