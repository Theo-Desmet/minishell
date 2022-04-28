/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:32:13 by bbordere          #+#    #+#             */
/*   Updated: 2021/11/25 15:54:11 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*ptr;
	int				i;

	i = 0;
	ptr = s;
	c = (unsigned char) c;
	while (len--)
	{
		ptr[i] = c;
		i++;
	}
	return (s);
}
