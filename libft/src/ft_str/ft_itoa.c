/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:55:03 by bbordere          #+#    #+#             */
/*   Updated: 2021/11/26 14:17:16 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_number_size(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	ft_strrev(char *str)
{
	size_t	i;
	size_t	len;
	char	temp;

	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	nb;

	i = 0;
	nb = (unsigned) n;
	str = malloc((ft_number_size(n) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[ft_number_size(n)] = '\0';
	if (n < 0)
	{
		nb = -nb;
		str[ft_number_size(n) - 1] = '-';
	}
	else if (nb == 0)
		str[ft_number_size(n) - 1] = '0';
	while (nb != 0)
	{		
		str[i++] = nb % 10 + '0';
		nb /= 10;
	}
	ft_strrev(str);
	return (str);
}
