/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:10:59 by tdesmet           #+#    #+#             */
/*   Updated: 2021/12/03 08:02:02 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*ptr1;
	unsigned char		*ptr2;

	i = 0;
	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (n > i)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
/*
int main()
{
	char s[] = {-128, 0, 127, 0};
	char s1[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};

	printf("%d", ft_memcmp(s, s1, 4));
}*/
