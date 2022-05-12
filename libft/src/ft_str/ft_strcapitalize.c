/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:56:23 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/23 20:56:23 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		if ((i == 0) || (str[i] && str[i - 1] >= ' ' && str[i - 1] <= '/')
			|| (str[i - 1] >= '[' && str[i - 1] <= '`')
			|| (str[i - 1] >= ':' && str[i - 1] <= '@')
			|| (str[i - 1] >= '{'))
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] -= 32;
		}
		if (str[i + 1] && str[i + 1] >= 'A' && str[i + 1] <= 'Z')
			str[i + 1] += 32;
		i++;
	}
	return (str);
}
