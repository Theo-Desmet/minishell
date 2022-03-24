/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:57:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/24 15:49:16 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*ft_init_path(void)
{
	t_data	*data;
	char	*buf1;
	char	*buf2;

	buf1 = NULL;
	buf2 = NULL;
	data = malloc(sizeof(t_data));
	data->prev_path = getcwd(buf1, 0);
	data->actu_path = getcwd(buf2, 0);
	return (data);
}
