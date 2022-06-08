/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:00:14 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/08 11:31:47 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(t_data *data)
{
	char	*pwd;
	char	*temp;
	int		len;

	pwd = ft_strdup(data->pwd);
	temp = pwd;
	len = ft_strlen(pwd);
	if (pwd[len -1] == '\n')
		pwd[len - 1] = 0;
	pwd = ft_strdup(ft_strrchr(pwd, '/') + 1);
	free(temp);
	return (pwd);
}

char	*ft_get_user(t_data *data)
{
	char	*user;

	user = ft_getenv(data->env, "LOGNAME=");
	if (!user)
		return ("camarade");
	return (user - 1);
}

char	*ft_prompt(t_data *data)
{
	char	*prompt;
	char	*user;
	char	*pwd;

	pwd = ft_get_pwd(data);
	user = ft_get_user(data);
	prompt = ft_strjoin("\1\033[0;38;2;186;11;24m\2", user);
	prompt = ft_strjoin1(prompt, "@");
	prompt = ft_strjoin1(prompt, "OUR⭐SHELL");
	prompt = ft_strjoin1(prompt, "\1\033[0;37m\2:");
	prompt = ft_strjoin1(prompt, "\1\033[0;38;2;251;208;54m\2");
	prompt = ft_strjoin1(prompt, "/");
	prompt = ft_strjoin1(prompt, pwd);
	prompt = ft_strjoin1(prompt, "\1\033[0;37m\2❱ ");
	free(pwd);
	return (prompt);
}
