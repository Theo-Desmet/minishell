/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:15:30 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/05 14:32:46 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char	*s1, const char *s2)
{
	size_t		i;
	size_t		temp;
	int			j;
	char		*ptr;

	i = 0;
	ptr = (char *) s1;
	if (!s2 || !(*s2))
		return (&ptr[0]);
	while (s1[i])
	{
		temp = i;
		j = 0;
		while (s2[j] && s1[temp] == s2[j])
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
