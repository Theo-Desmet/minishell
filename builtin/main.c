/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:07:13 by tdesmet           #+#    #+#             */
/*   Updated: 2022/04/14 16:05:02 by tdesmet          ###   ########.fr       */
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

//	tab = ft_split("a HOME", ' ');
//	tab2 = ft_split("a /tmp", ' ');
//	tab3 = ft_split("cd /usr/bin/", ' ');
	data = ft_init_data(envp);
//	ft_echo(tab);
//	data->env = ft_export(data->env, tab);
//	ft_env(data->env);
//	data->env = ft_unset(data->env, tab);
//	ft_cd(data, tab2);
//	ft_pwd();
//	ft_env(data->env);
//	ft_wildcard(data->wd, "*in*");

	int	i;

	i = 0;
	tab4 = malloc(sizeof(t_token *) * 8);
	while (i < 7)
	{
		tab4[i] = malloc(sizeof(t_token));
		i++;
	}
	tab4[0]->val = "<";
	tab4[0]->type = R_IN;
	tab4[1]->val = "in";
	tab4[1]->type = IN_FILE;
	tab4[2]->val = "cat";
	tab4[2]->type = WORD;
	tab4[3]->val = ">";
	tab4[3]->type = R_OUT;
	tab4[4]->val = "ou";
	tab4[4]->type = OUT_A_FILE;
	tab4[5]->val = "<<";
	tab4[5]->type = R_HERE_DOC;
	tab4[6]->val = "in2";
	tab4[6]->type = OUT_FILE;
	tab4[7] = NULL;
	ft_glhf(tab4, data->env, data);
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
	ft_lstdel_all(data->env);
	ft_lstdel_all(data->wd);
	free(data);
}
