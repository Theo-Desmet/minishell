/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:16:00 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/14 17:26:27 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	neg;

	i = 0;
	neg = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}	
	result *= neg;
	return (result);
}

/*int main ()
{
	printf("%d", atoi(" \t \n \v \f \r ---1"));
	printf("\n%d", ft_atoi(" \t \n \v \f \r ---1"));
}*/
