/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:34:32 by bbordere          #+#    #+#             */
/*   Updated: 2021/11/26 14:33:05 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		end;
	size_t		start;
	char		*str;
	char		*src;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	src = (char *) s1;
	while (*src && ft_strchr(set, *src))
	{
		start++;
		src++;
	}
	end = ft_strlen(src);
	while (end && ft_strrchr(set, src[end]))
		end--;
	str = ft_substr(s1, start, end + 1);
	return (str);
}
