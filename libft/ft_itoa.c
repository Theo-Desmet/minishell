/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 07:35:08 by tdesmet           #+#    #+#             */
/*   Updated: 2021/11/30 07:49:31 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		neg;

	neg = 0;
	if (n < 0)
		neg = 1;
	str = malloc(ft_nbrlen(n) + neg + 1);
	if (!str)
		return (0);
	i = ft_nbrlen(n) + neg;
	str[i] = 0;
	i--;
	while (i >= 0)
	{
		if (n < 0)
			str[i] = n % 10 * -1 + 48;
		else
			str[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}
/*
int main()
{
	printf("%s",ft_itoa(0));
}*/
