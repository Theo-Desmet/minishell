/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:19:52 by tdesmet           #+#    #+#             */
/*   Updated: 2021/11/30 09:14:05 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char	*s1, const char *s2, size_t len)
{
	size_t		i;
	size_t		temp;
	int			j;
	char		*ptr;

	i = 0;
	ptr = (char *) s1;
	if (!s2[0])
		return (&ptr[0]);
	if (len == 0)
		return (0);
	while (s1[i] && len > i)
	{
		temp = i;
		j = 0;
		while (s1[temp] == s2[j] && len > temp)
		{
			temp++;
			j++;
			if (s2[j] == 0)
				return (&ptr[i]);
		}
		i++;
	}
	return (0);
}
/*
int main()
{
	printf("%s", ft_strnstr("aaabcabcd", "a", -1));
	//printf("\n%s", strnstr("le pain et le fromage ces ma vie", "le p", 4));
}*/
