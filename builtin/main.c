/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:07:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/12 14:12:00 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define PATH_MAX 4096

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	**tab;
	char	**tab2;
	char	**tab3;
	t_token **tab4;

//	tab = ft_split("export T=1 T2=2", ' ');
//	tab2 = ft_split("unset T T2 ", ' ');
//	tab3 = ft_split("cd /usr/bin/", ' ');
	data = ft_init_data(envp);
//	ft_echo(tab);
//	ft_cd(data, tab2);
//	ft_pwd();
//	data->env = ft_export(data->env, tab);
//	ft_env(data->env);
//	data->env = ft_unset(data->env, tab2);
//	ft_env(data->env);
//	ft_wildcard(data->wd, "*in*");
//	ft_lstdel_all(data->env);
//	ft_lstdel_all(data->wd);

	int	i;

	i = 0;
	tab4 = malloc(sizeof(t_token *) * 4);
	while (i < 3)
	{
		tab4[i] = malloc(sizeof(t_token));
		i++;
	}
	tab4[0]->val = "<";
	tab4[0]->type = 11;
	tab4[1]->val = "test1";
	tab4[1]->type = 4;
	tab4[2]->val = "cat";
	tab4[2]->type = 3;
	tab4[3] = NULL;
	ft_redirection(tab4, STDIN_FILENO);
/*
	char *input;
	ft_init_sig();
	while(1)
	{
		input = readline("Prompt > ");
		if (!input)
			break ;
		add_history(input);
	printf("%s", input);
	}
	printf("exit");
*/
	free(data);
}
