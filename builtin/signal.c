/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:28:09 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/11 17:04:54 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_int(int sig)
{
	ft_putstr("\nPrompt > ");
}

void	ft_init_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int);
}
