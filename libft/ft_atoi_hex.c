/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:27:58 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/22 08:17:56 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s || !(*s))
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_base(char *base)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = ft_strlen(base);
	if (len == 0 || len == 1)
		return (0);
	while (++i < len)
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if ((base[i] >= 9 && base[i] <= 13) || base[i] == ' ')
			return (0);
		j = i;
		while (++j < len)
			if (base[i] == base[j])
				return (0);
	}
	return (1);
}

int	find_index(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	nb;
	int	minus;

	nb = 0;
	minus = 0;
	if (check_base(base) == 0)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus++;
		str++;
	}
	while (find_index(*str, base) != -1)
	{
		nb = nb * ft_strlen(base) + find_index(*str, base);
		str++;
	}
	if (minus % 2)
		return (nb * -1);
	return (nb);
}

int	ft_atoi_hex(char *str)
{
	int	i;
	int	result;

	i = 0;
	if (str[0] == '0' && str[1] == 'x')
		str = &str[2];
	while (str[i] && (str[i] < 'A' || str[i] > 'F'))
		i++;
	if (str[i] >= 'A' && str[i] <= 'Z')
		result = ft_atoi_base(str, "0123456789ABCDEF");
	else
		result = ft_atoi_base(str, "0123456789abcdef");
	return (result);
}
