/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:48:23 by bbordere          #+#    #+#             */
/*   Updated: 2022/06/05 12:17:18 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_inter(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_global.rtn_val = 130;
	}
	else if (sig == SIGTSTP || sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

void	sig_handler(int sig)
{
	if (g_global.in_exec == 0)
		ft_sig_inter(sig);
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_global.rtn_val = 130;
		kill(g_global.pid, SIGINT);
	}
	else if (sig == SIGTSTP)
	{
		ft_putstr_fd("\nStopped\n", 1);
		g_global.rtn_val = 148;
		kill(g_global.pid, SIGSTOP);
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	else if (sig == SIGSEGV)
		ft_putstr_fd("Segmentation fault\n", 1);
	else if (sig == SIGABRT)
		ft_putstr_fd("Abort\n", 1);
}

int	ft_sig_init(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGTSTP, &sig_handler);
	signal(SIGABRT, &sig_handler);
	signal(SIGSEGV, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	g_global.in_exec = 0;
	g_global.pid = -1;
	g_global.rtn_val = 0;
	return (1);
}
