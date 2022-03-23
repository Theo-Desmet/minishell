/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 08:43:24 by tdesmet           #+#    #+#             */
/*   Updated: 2021/11/30 08:31:35 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int		i;
	char	*ptr;

	if (n == 0)
		return (0);
	if (c > 256)
		c %= 256;
	i = 0;
	ptr = (char *) s;
	while (n -1 && ptr[i] != c)
	{
		n--;
		i++;
	}
	if (ptr[i] == c)
		return (&ptr[i]);
	else
		return (0);
}
/*
int main ()
{
	char s[] = {0, 1, 2 ,3 ,4 ,5};

	//printf("%s\n", memchr("salut", 'a', 1));
	printf("%s", ft_memchr(s, 2 + 256, 3));
}*/
