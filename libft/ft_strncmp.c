/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 08:10:34 by tdesmet           #+#    #+#             */
/*   Updated: 2021/11/30 08:49:44 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && n - 1)
	{
		i++;
		n--;
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (s1[i] == '\0')
			return (-1);
		if (s2[i] == '\0')
			return (1);
	}
	return (s1[i] - s2[i]);
}
/*
int main ()
{
	printf("%d", ft_strncmp("chat\200", "chat\0", 6));
	printf("\n%d", strncmp("chat\200", "chat\0", 6));
}*/
