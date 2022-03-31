/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:24:23 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/31 10:03:58 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h> 
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h> 
# include <sys/ioctl.h> 
# include <sys/types.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structure.h"
# include "../libft/libft.h"

		/********************************
		*				*
		*	     builtin		*
		*				*
		*********************************/

int		ft_cd(t_data *data, char **str);
int		ft_cd_error(char *str);
int		ft_cd_home(t_data *data, char *str);
char	*ft_getenv(t_list **env, char *str);

int	ft_echo(char **args);
int	ft_check_option(char **args);

int     ft_env(t_list **env);

t_list	**ft_export(t_list **env, char **arg);
void	ft_add_env(t_list **env, char *str, char *name);
void	ft_print_export(char *name);
void	ft_sort_export(t_list **env);
char	*ft_name_env(char *str);
int		ft_check_export_arg(char *str);
int		ft_env_size(t_list **env);

t_data	*ft_init_data(char **envp);
t_list	**ft_init_env(t_list **env, char **envp);

int		ft_pwd(t_data *data);
void	ft_update_env(t_list **env, char *name, char *value);

t_list	**ft_unset(t_list **env, char **arg);
void	ft_del_env(t_list **env, char *str);
int		ft_check_unset_arg(char *str);
#endif
