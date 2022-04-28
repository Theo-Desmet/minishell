/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:30:45 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/01 11:14:50 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_args(va_list ap, const char *str, int *i)
{
	while (*str)
	{
		if (*str == '%' && *(str + 1) == 'c')
			ft_putchar(va_arg(ap, int), i);
		if (*str == '%' && *(str + 1) == 's')
			ft_putstr(va_arg(ap, char *), i);
		if (*str == '%' && (*(str + 1) == 'i' || *(str + 1) == 'd'))
			ft_putnbr(va_arg(ap, int), i);
		if (*str == '%' && *(str + 1) == 'u')
			ft_putnbr_base(va_arg(ap, unsigned int), DECIMAL_BASE, i);
		if (*str == '%' && *(str + 1) == 'x')
			ft_putnbr_base(va_arg(ap, unsigned int), HEXA_BASE_L, i);
		if (*str == '%' && *(str + 1) == 'X')
			ft_putnbr_base(va_arg(ap, unsigned int), HEXA_BASE_U, i);
		if (*str == '%' && *(str + 1) == 'p')
			ft_put_address(va_arg(ap, void *), i);
		if (*str == '%' && *(str + 1) == '%')
			ft_putchar('%', i);
		if (*str == '%')
			str++;
		else
			ft_putchar(*str, i);
		str++;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			i;

	i = 0;
	va_start(ap, str);
	ft_args(ap, str, &i);
	va_end(ap);
	return (i);
}
