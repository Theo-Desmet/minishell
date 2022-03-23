/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:05:27 by tdesmet           #+#    #+#             */
/*   Updated: 2021/11/28 15:17:21 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *) s;
	while (n)
	{
		ptr[i] = c;
		i++;
		n--;
	}
	return (s);
}
/*
int main() {

    int tab [] = { 54, 85, 20, 63, 21 };
    size_t size = sizeof( int ) * 5;
    int i;

    for( i=0; i<5; i++) {
        printf( "%d ", tab[i] );
    }

    printf( "\n" );
    ft_memset( tab, 0, size );

    for( i=0; i<5; i++) {
        printf( "%d ", tab[i] );
    }

    return 0;
}*/
