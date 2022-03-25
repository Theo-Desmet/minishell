/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:07:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/25 15:45:04 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define PATH_MAX 4096

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	**tab;

	tab = ft_split("T=", ' ');
	data = ft_init_data(envp);
	data->env = ft_export(data->env, tab);
	ft_env(data->env);
	free(data->actu_path);
	free(data->prev_path);
	free(data);
}
