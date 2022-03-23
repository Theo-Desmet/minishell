/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:07:14 by tdesmet           #+#    #+#             */
/*   Updated: 2022/02/24 10:02:24 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char				*ptr;
	unsigned int		i;
	unsigned int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	ptr = malloc(sizeof(char) * i + sizeof(char) * j + 1);
	if (!ptr)
		return (0);
	ft_memcpy(ptr, s1, i);
	ft_memcpy(ptr + i, s2, j);
	ptr[i + j] = 0;
	if (s1)
		free(s1);
	return (ptr);
}
