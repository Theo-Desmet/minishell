/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:48:37 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/23 20:48:37 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*res;
	size_t	c_size;

	if (!ptr)
		return (malloc(size));
	c_size = sizeof(ptr);
	if (size <= c_size)
		return (ptr);
	res = malloc(size);
	if (!res)
		return (NULL);
	ft_memcpy(res, ptr, c_size);
	free(ptr);
	return (res);
}
