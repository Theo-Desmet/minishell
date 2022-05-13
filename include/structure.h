/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:35:26 by tdesmet           #+#    #+#             */
/*   Updated: 2022/05/13 12:07:22 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
enum    e_type
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
    T_FILE = 17,
    D_QUOTE = 18,
    S_QUOTE = 19,
    IN_FILE = 20,
    OUT_FILE = 21,
    DELIMITER = 22,
    OUT_A_FILE = 23
};

typedef struct s_token
{
	char	*val;
	int		type;
}	t_token;

typedef struct s_temp
{
	char	**vars;
	char	*str;
	t_list	**env;
	size_t	i;
	size_t	j;
}	t_temp;

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
	int		fd_in;
	int		fd_out;
	int		rtn_val;
	int		nb_heredoc;
	int		act_heredoc;
	char		*pwd;
}	t_data;
#endif
