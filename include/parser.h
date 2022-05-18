/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:20:53 by bbordere          #+#    #+#             */
/*   Updated: 2022/05/12 08:33:41 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define ERROR_MSG "minishell: syntax error near unexpected token "

int		ft_check_op(t_token **tokens, size_t	i);
int		ft_isvalidtype(int type);
size_t	ft_tab_size(t_token	**tokens);
int		ft_isop(int type);
int		ft_check_grammar(t_token **tokens);
int		ft_check_quotes(t_token	*token);
int		ft_check_here_doc(t_token **tokens, size_t i);
void	ft_check_builtin(t_token **tokens);

#endif
