/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:07:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/31 09:47:02 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define PATH_MAX 4096

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	**tab;
	char	**tab2;
	char	**tab3;

	tab = ft_split("TEST=1 ca marche ces pas possible je vais omg", ' ');
	tab2 = ft_split("test/2", ' ');
	tab3 = ft_split("", ' ');
	data = ft_init_data(envp);
	
	ft_cd(data, tab3);
	ft_pwd(data);
	ft_cd(data, tab3);
	ft_pwd(data);
/*
	data->env = ft_export(data->env, tab);
	ft_cd(data, tab3);
	ft_pwd(data);
	data->env = ft_unset(data->env, tab);
	ft_cd(data, tab3);
*/

	ft_pwd(data);
	ft_env(data->env);
	ft_echo(tab);
	ft_lstdel_all(data->env);
	free(data);
}
