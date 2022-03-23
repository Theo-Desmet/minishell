/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:21:49 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/22 08:18:18 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*ptr;

	if (len == 0 || start > ft_strlen(s))
	{
		ptr = malloc(1);
		ptr[0] = 0;
		return (ptr);
	}
	i = ft_strlen(&s[start]);
	if (i < len)
		len = i;
	i = 0;
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (0);
	while (s[start] && len)
	{
		ptr[i] = s[start];
		i++;
		start++;
		len --;
	}
	ptr[i] = 0;
	return (ptr);
}
/*
int main ()
{
	char str[] = "SydAONcU3FJWP eslgPNq21I";
	printf("%s\n", str);
	printf("%s", ft_substr(str, 7, 4));
}*/
