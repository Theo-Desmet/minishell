/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:24:23 by tdesmet           #+#    #+#             */
/*   Updated: 2022/03/24 15:50:36 by tdesmet          ###   ########.fr       */
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

#endif
