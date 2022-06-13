/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:24:23 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/13 16:52:50 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "init.h"
# include "exec.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "lexer.h"
# include <errno.h>
# include "struct.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h> 
# include <dirent.h>
# include "parser.h"
# include <string.h>
# include <termios.h>
# include "builtin.h"
# include <sys/stat.h>
# include <sys/wait.h> 
# include <sys/ioctl.h> 
# include <sys/types.h>
# include "expansions.h"
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>

#endif
