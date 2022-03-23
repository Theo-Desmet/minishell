/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:15:48 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/15 12:11:53 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *) s;
	if (c > 256)
		c %= 256;
	while (ptr[i])
		i++;
	while (i >= 0)
	{
		if (ptr[i] == c)
			return (&ptr[i]);
		i--;
	}
	return (0);
}

/*int main()
{
	printf("%s", ft_strrchr("coucou", 0));
	printf("\n%s", strrchr("coucou", 0));
}*/
