/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:58:50 by tdesmet           #+#    #+#             */
/*   Updated: 2021/11/28 15:19:37 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		i;
	char	*ptr;
	char	*ptr2;

	i = 0;
	ptr = (char *) dest;
	ptr2 = (char *) src;
	while (n)
	{
		ptr[i] = ptr2[i];
		i ++;
		n--;
	}
	return (dest);
}
/*int main()
{

    int	tab1 [] = {54, 85, 20, 63, 21};
    int	tab2 [] = {1, 2, 3, 4, 5};
    int	size = sizeof( int ) * 5;
    int	i;

    for( i=0; i<5; i++) {
        printf( "%d ", tab2[i] );
    }

    printf( "\n" );
    ft_memcpy( tab2, tab1, size);

    for( i=0; i<5; i++) {
        printf( "%d ", tab2[i] );
    }
}*/
