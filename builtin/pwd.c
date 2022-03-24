/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:00:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/24 15:47:44 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_actual_path(t_data *data)
{
	char	*cwd;
	char	buf[PATH_MAX];
	char	*temp;

	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		return (0);
	temp = ft_strdup(cwd);
	free(data->prev_path);
	data->prev_path = data->actu_path;
	data->actu_path = temp;
	return (1);
}

int	ft_pwd(t_data *data)
{
	printf("%s\n", data->actu_path);
	return (1);
}
