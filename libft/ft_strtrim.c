/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:40:32 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/15 12:15:41 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_setchr(char *s1, char *set, int i, int dir)
{
	int	chr;
	int	result;

	chr = 0;
	result = 0;
	while (set[chr])
	{
		if (dir == -1 && i == 0)
			return (result);
		if (s1[i] == set[chr])
		{
			chr = 0;
			result++;
			i += dir;
		}
		else
			chr++;
	}
	if (dir == -1)
		return (i);
	else
		return (result);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		start;
	int		end;
	int		dir;
	char	*trm;

	i = 0;
	dir = 1;
	start = ft_setchr(s1, set, i, dir);
	i = ft_strlen(s1);
	dir = -1;
	end = ft_setchr(s1, set, i - 1, dir);
	trm = malloc(end - start + 2);
	if (!trm)
		return (0);
	i = 0;
	while (start <= end)
	{
		trm[i] = s1[start];
		i++;
		start++;
	}
	trm[i] = 0;
	return (trm);
}
