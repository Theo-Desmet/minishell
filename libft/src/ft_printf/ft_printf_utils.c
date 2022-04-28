/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:37:30 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/06 11:10:29 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n, int *i)
{
	unsigned int	nbr;

	if (n < 0)
	{
		nbr = -n;
		ft_putchar('-', i);
	}
	else
		nbr = n;
	if (n / 10)
		ft_putnbr(nbr / 10, i);
	ft_putchar((nbr % 10) + '0', i);
}

void	ft_putnbr_base(unsigned long n, char *base, int *i)
{
	size_t	len;

	len = ft_strlen(base);
	if (n / len)
		ft_putnbr_base(n / len, base, i);
	ft_putchar(base[n % len], i);
}

void	ft_put_address(void	*p, int *i)
{
	unsigned long int	addr;

	addr = (unsigned long)p;
	if (addr == 0)
	{
		ft_putstr(NULL_PTR, i);
		return ;
	}
	ft_putstr("0x", i);
	ft_putnbr_base(addr, HEXA_BASE_L, i);
}

void	ft_putstr(char *str, int *i)
{
	if (!str)
	{
		ft_putstr(NUL_STR, i);
		return ;
	}
	*i += write(1, str, ft_strlen(str));
}

void	ft_putchar(int c, int *i)
{
	*i += write(1, &c, 1);
}
