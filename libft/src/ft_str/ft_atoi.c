/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:51:26 by bbordere          #+#    #+#             */
/*   Updated: 2021/11/25 10:02:22 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	s;

	i = 0;
	s = 1;
	res = 0;
	while (str[i] && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '-' && str[i])
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+' && str[i])
		i++;
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (s * res);
}
