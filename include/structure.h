/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:35:26 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/01 11:02:03 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include "../libft/libft.h"

typedef struct s_lists{
	char			*str;
	int				type;
	struct s_list	*before;
	struct s_list	*next;
}	t_lists;

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
	char	*cmd;
	char	*path;
}	t_cmd;

typedef struct s_data{
	t_parsing	parsing;
	t_arg		arg;
	t_cmd		cmd;
	t_list		**env;
	t_list		**wd;
}	t_data;
#endif
