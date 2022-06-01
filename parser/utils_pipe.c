/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:55:23 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/01 18:57:09 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

int	ft_get_return_val(int status)
{
	if ((g_global.rtn_val == 130 || g_global.rtn_val == 148)
		&& g_global.in_exec == 1)
		return (g_global.rtn_val);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	ft_wait_all(t_data *data)
{
	int		status;
	int		res;
	ssize_t	i;

	res = 0;
	i = -1;
	status = 0;
	while (data->childs[++i])
	{
		waitpid(data->childs[i], &status, WUNTRACED);
		res = ft_get_return_val(status);
	}
	return (res);
}

int	ft_glhf(char *args, char *args2)
{
	int	i;

	i = 0;
	while (args[i] && args2[i])
	{
		if (args[i] != args2[i])
			return (0);
		i++;
	}
	if (!args2[i] || args2[i] == ' ')
		return (1);
	return (0);
}
