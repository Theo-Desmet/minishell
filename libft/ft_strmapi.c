/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 07:34:07 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/15 12:16:28 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	if (f == 0 || s == 0)
		return (0);
	ptr = malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (0);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = 0;
	i = 0;
	while (ptr[i])
	{
		ptr[i] = (*f)(i, ptr[i]);
		i++;
	}
	return (ptr);
}
