/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:24:23 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/25 15:22:51 by tdesmet          ###   ########.fr       */
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

int		ft_cd(t_data *data, char *str);
int		ft_cd2(t_data *data, char *str);
int		ft_get_actual_path(t_data *data);
int		ft_pwd(t_data *data);
int		ft_env(t_list **env);
void		ft_init_path(t_data *data);
t_data	*ft_init_data(char **envp);
t_list	**ft_export(t_list **env, char **arg);

#endif
