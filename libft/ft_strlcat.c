/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:42:53 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/15 12:07:30 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = ft_strlen(dst);
	k = ft_strlen(src);
	if (size <= j)
		return (size + k);
	while (src[i] && ((size - 1) > (j + i)))
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (k + j);
}
/*
int main ()
{
	char dest[10] = "a";	
	
	printf("\n%d, %s", ft_strlcat(dest, "lorem ipsum dolor sit amet", 5), dest);
}*/
