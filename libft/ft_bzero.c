/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:25:01 by tdesmet           #+#    #+#             */
/*   Updated: 2021/11/28 15:17:11 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *) s;
	while (n)
	{
		ptr[i] = 0;
		i++;
		n--;
	}
}
/*
int main()
{

    int	tab [] = { 54, 85, 20, 63, 21 };
    int	size = sizeof( int ) * 5;
    int	i;

    for( i=0; i<5; i++) {
        printf( "%d ", tab[i] );
    }

    printf( "\n" );
    ft_bzero( tab, size);

    for( i=0; i<5; i++) {
        printf( "%d ", tab[i] );
    }

    return 0;
}*/
