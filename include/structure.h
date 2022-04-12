/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:35:26 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/12 08:25:14 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include "../libft/libft.h"

enum	e_type
{
	WORD = 1,
	PIPE = 2,
	CMD = 3,
	ARGS = 4,
	D_PIPE = 5,
	AND = 6,
	D_AND = 7,
	I_PAR = 8,
	O_PAR = 9,
	VAR = 10,
	R_IN = 11,
	R_HERE_DOC = 12,
	R_OUT = 13,
	R_APPEND = 14,
	T_NULL = 15,
	WILDCARD = 16,
	T_FILE = 17
};

typedef struct s_token
{
	char	*val;
	int		type;
}	t_token;

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
