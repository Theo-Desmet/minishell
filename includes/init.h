/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:19:33 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/13 17:18:17 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "struct.h"

void	ft_exec_prompt(t_data *data);
void	ft_exit_prompt(t_data *data);
void	ft_update_shlvl(t_list **env);
int		ft_get_cmd_line(t_data *data);

void	ft_free_data(t_data *data);
void	ft_free_data(t_data *data);
void	ft_free_lexer(t_data *data);
void	ft_lstdel_all(t_list **lst);
void	*ft_free_tokens(t_token **tokens);
void	ft_quit(t_data *data, char *here_doc, int fork);

t_lexer	*ft_init_lexer(void);
t_list	**ft_init_wd(t_list **wd);
char	*ft_init_pwd(t_data *data);
t_data	*ft_init_data(char **envp);
t_list	**ft_init_env(t_list **env, char **envp);

char	*ft_color_rtn_val(void);
char	*ft_prompt(t_data *data);
char	*ft_get_pwd(t_data *data);
char	*ft_get_user(t_data *data);

int		ft_sig_init(void);
void	sig_handler(int sig);
void	ft_sig_inter(int sig);

void	ft_close_all(t_data *data);
char	**ft_lst_to_tab(t_list **lst);
void	ft_update_type(t_token **tokens, int mode);
void	ft_update_files(t_token **tokens, size_t i);

#endif
