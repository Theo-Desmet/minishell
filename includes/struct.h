/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:14:11 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/01 15:44:23 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"

enum	e_type
{
	WORD = 1,
	PIPE = 2,
	BUILDIN = 3,
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

typedef struct s_lexer
{
	t_token	**tokens;
	char	**lexed;
	char	*input;
}	t_lexer;

typedef struct s_data{
	t_list	**env;
	t_list	**wd;
	t_lexer	*lexer;
	pid_t	*childs;
	int		**pipes;
	int		fd_in;
	int		fd_out;
	int		rtn_val;
	int		nb_heredoc;
	int		act_heredoc;
	int		nb_pipes;
	char	*pwd;
}	t_data;

typedef struct s_global
{
	int		in_exec;
	int		pid;
	int		rtn_val;
	char	*prompt;
}	t_global;

extern t_global	g_global;

typedef struct s_temp
{
	char	**vars;
	char	*str;
	t_list	**env;
	size_t	i;
	size_t	j;
}	t_temp;

#endif
