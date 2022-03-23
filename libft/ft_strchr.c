/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:01:35 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/15 12:11:38 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *) s;
	if (c > 256)
		c %= 256;
	while (ptr[i])
	{
		if (ptr[i] == c)
			return (&ptr[i]);
		i++;
	}
	if (c == 0)
		return (&ptr[i]);
	return (0);
}
/*
int main()
{
	printf("%s",ft_strchr("coucou", 0));
	printf("\n%s",strchr("coucou", 0));
}*/
