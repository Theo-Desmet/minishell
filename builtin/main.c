/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:07:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/24 15:49:51 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define PATH_MAX 4096

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_init_path();
	ft_pwd(data);
	ft_cd(data, argv[1]);
	ft_pwd(data);
	ft_cd(data, "-");
	ft_pwd(data);
	ft_cd(data, "-");
	ft_pwd(data);
	ft_cd(data, "~/");
	ft_pwd(data);
	ft_cd(data, "~/Documents");
	ft_pwd(data);
	ft_cd(data, "sdasdasdxza//dasdsds/dsadsad/asd/asd/s/dsa/");
	ft_pwd(data);
	ft_cd(data, "-");
	ft_pwd(data);
	ft_cd(data, "/bin");
	ft_pwd(data);
	ft_cd(data, "-");
	ft_pwd(data);
	ft_pwd(data);
	ft_pwd(data);
	free(data->actu_path);
	free(data->prev_path);
	free(data);
}
