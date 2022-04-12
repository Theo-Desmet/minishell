/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:49:00 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/05 14:54:08 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr_len(const char *s1, const char *s2)
{
	size_t		i;
	size_t		temp;
	int			j;

	i = 0;
	if (!s2 || !(*s2))
		return (i);
	while (s1[i])
	{
		temp = i;
		j = 0;
		while (s2[j] && s1[temp] == s2[j])
		{
			temp++;
			j++;
			if (s2[j] == 0)
				return (i);
		}
		i++;
	}
	return (0);
}

