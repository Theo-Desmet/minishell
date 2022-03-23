/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:35:26 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/23 11:21:14 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

global int SIGRET;

typedef struct s_list{
	int	val;
	int	before;
	int	next;
}	t_list;

typedef struct s_data{
	t_parsing	parsing;
	t_arg		arg;
	t_cmd		cmd;
	char *actual_path;
}	t_data;

typedef struct s_parsing{
	int	nb_args;
	int	nb_cmd;
	int	nb_pipe;
}	t_parsing;

typedef struct s_arg{
	int	arg[2];
	int	nb_arg;
}	t_arg;

typedef struct s_cmd{
	char *cmd;
	char *path;
}	t_cmd;
#endif
