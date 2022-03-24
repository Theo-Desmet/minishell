/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:35:26 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/24 16:08:39 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_lists{
	char			*str;
	int				type;
	struct s_list	*before;
	struct s_list	*next;
}	t_lists;

typedef struct s_ast_node{
	struct s_ast_info	*info;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_ast_info{

}	t_ast_info;

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
	char		*actu_path;
	char		*prev_path;
}	t_data;
#endif
