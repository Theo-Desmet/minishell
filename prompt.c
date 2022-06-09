/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:00:14 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/09 14:16:00 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(t_data *data)
{
	char	*pwd;
	char	*temp;
	int		len;

	pwd = ft_strdup(data->pwd);
	if (!pwd)
		return (NULL);
	temp = pwd;
	len = ft_strlen(pwd);
	if (pwd[len -1] == '\n')
		pwd[len - 1] = 0;
	pwd = ft_strdup(ft_strrchr(pwd, '/') + 1);
	if (!pwd)
		return (NULL);
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

char	*ft_color_rtn_val(void)
{
	if (!g_global.rtn_val)
		return ("\1\033[0;37m\2❱ ");
	else
		return ("\1\033[0;38;2;186;11;24m\2❱ \1\033[0;37m\2");
}

char	*ft_prompt(t_data *data)
{
	char	*prompt;
	char	*user;
	char	*pwd;
	char	*color;

	pwd = ft_get_pwd(data);
	user = ft_get_user(data);
	color = ft_color_rtn_val();
	prompt = ft_strjoin("\1\033[0;38;2;186;11;24m\2", user);
	prompt = ft_strjoin1(prompt, "@");
	prompt = ft_strjoin1(prompt, "OUR⭐SHELL");
	prompt = ft_strjoin1(prompt, "\1\033[0;37m\2:");
	prompt = ft_strjoin1(prompt, "\1\033[0;38;2;251;208;54m\2");
	prompt = ft_strjoin1(prompt, "/");
	prompt = ft_strjoin1(prompt, pwd);
	prompt = ft_strjoin1(prompt, color);
	free(pwd);
	if (!prompt)
		return ("ourshell>");
	return (prompt);
}
