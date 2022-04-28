/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:28:52 by bbordere          #+#    #+#             */
/*   Updated: 2022/04/28 12:35:34 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "expansions/expansions.h"
#include "parser/parser.h"
#include <readline/readline.h>
#include <readline/history.h>

void	ft_check_separator(t_data *data, t_token **args, t_list **env);

t_list	**ft_init_env(t_list **env, char **envp)
{
	size_t	i;
	t_list	*temp;
	char	*value;
	int		lenght;

	env = malloc(sizeof(t_list));
	if (!env)
		return (NULL);
	*env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		ft_lstadd_back(env, ft_lstnew(envp[i]));
		i++;
	}
	temp = *env;
	while (temp)
	{
		value = temp->content;
		lenght = ft_strlen(value);
		temp->content = ft_strdup(value);
		temp = temp->next;
	}
	return (env);
}

t_list	**ft_init_wd(t_list **wd)
{
	wd = malloc(sizeof(t_list));
	if (!wd)
		return (NULL);
	*wd = NULL;
	return (wd);
}

t_data	*ft_init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);//modifier secu err dans main
	data->env = ft_init_env(data->env, envp);
	if (!data->env)
		return (NULL);
	data->wd = ft_init_wd(data->wd);
	if (!data->wd)
		return (NULL);
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	data->rtn_val = 0;
	data->nb_heredoc = 0;
	data->act_heredoc = -1;
	return (data);
}

void	ft_lstdel_all(t_list **lst)
{
	t_list	*temp;

	if (!lst)
		return ;
	temp = *lst;
	while (lst && *lst)
	{
		(*lst) = (*lst)->next;
		free(temp->content);
		free(temp);
		temp = *lst;
	}
	free(lst);
}

void	*ft_free_tokens(t_token **tokens)
{
	size_t	i;

	i = 0;
	if (!tokens)
		return (NULL);
	while (tokens[i])
	{
		free(tokens[i]->val);
		i++;
	}
	ft_free((void **)tokens);
	tokens = NULL;
	return (NULL);
}

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("%s {%d} |%p| -> ", ((t_token *)lst->content)->val, ((t_token *)lst->content)->type, lst);
		lst = lst->next;
	}
	printf("NULL\n");
}

void	ft_update_type(t_token **tokens, int mode) // Mode sert juste a rechanger le type des wildcards qui ont deja ete expand 
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (mode == 1)
			if (tokens[i]->type == WILDCARD)
				tokens[i]->type = WORD;
		if (i != 0 && tokens[i - 1])
		{
			if (tokens[i - 1]->type == R_OUT)
				tokens[i]->type = OUT_FILE;
			else if (tokens[i - 1]->type == R_IN)
				tokens[i]->type = IN_FILE;
			else if (tokens[i - 1]->type == R_HERE_DOC)
				tokens[i]->type = DELIMITER;
			else if (tokens[i - 1]->type == R_APPEND)
				tokens[i]->type = OUT_A_FILE;
		}
		i++;
	}	
}

void	ft_free_loop(void **lexed, void **regrouped, t_token **tokens, t_token **final)
{
	if (lexed)
		ft_free((void **)lexed);
	if (regrouped)
		ft_free((void **)regrouped);
	if (tokens)
		ft_free_tokens(tokens);
	if (final)
		ft_free_tokens(final);
	lexed = NULL;
	regrouped = NULL;
	tokens = NULL;
	final = NULL;
}

/*
Pour skip suppress les leaks de readline avec valgrind : valgrind --suppressions=rl ./minishell
*/

int main(int ac, char **av, char **env)
{
	t_data *data;
	t_token **tokens; //Premier tableau de tokens
	t_token	**final; // Tableau de tokens une fois regroupe
	char	**lexed; // Tableau des strings une fois "lexee"
	char	*input;
	char	**regrouped; // Tableau des strings "regroupees"
	
	data = ft_init_data(env);
	while (1)
	{
		input = NULL;
		lexed = NULL;
		tokens = NULL;
		final = NULL;
		regrouped = NULL;

		input = readline("minishell > ");
		if (!input)
			break ;
		if (ft_strcmp(input, "\n"))
		{
			add_history(input);
			lexed = ft_lexer(input);
			tokens = ft_tokenize(lexed);
			if (!ft_check_grammar(tokens)) // Renvoie le msg d'erreur dans la fonction ft_check_grammar
			{
				ft_free((void **)lexed);
				ft_free_tokens(tokens);
				free(input);
				continue ;
			}
			ft_update_type(tokens, 0);
			ft_expand(tokens, data->env, data->wd);
			regrouped = ft_join(tokens);
			final = ft_tokenize(regrouped);
			ft_update_type(final, 1);
			// ft_check_builtin(final);  //Desactiver pour les tests de pipes
			ft_check_separator(data, final, data->env); // Changer le nom de la fonction
			ft_free_loop((void **)lexed, (void **)regrouped, tokens, final);
		}
		free(input);
	}
	printf("exit\n");
	rl_clear_history();

	ft_lstdel_all(data->env);
	ft_lstdel_all(data->wd);
	free(data);
	ft_free_loop((void **)lexed, (void **)regrouped, tokens, final);

	return (0);
}
