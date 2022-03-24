/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:51:41 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/24 15:46:03 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(t_data *data, char *str)
{
	char	*home;

	home = getenv("HOME");
	if (!str || !(*str))
	{
		if (!chdir(home))
		{
			ft_get_actual_path(data);
			return (1);
		}
	}
	else if (str[0] == '~')
	{
		home = ft_strjoin(home, &(str[1]));
		if (!chdir(home))
		{
			ft_get_actual_path(data);
			free(home);
			return (1);
		}
	}
	else
		return (ft_cd2(data, str));
}

int	ft_cd2(t_data *data, char *str)
{
	if (str[0] == '-')
	{
		if (!chdir(data->prev_path))
		{
			ft_get_actual_path(data);
			return (1);
		}
	}
	else if (!chdir(str))
	{
		ft_get_actual_path(data);
		return (1);
	}
	perror("getcwd() error");//a modifier
	return (0);
}
