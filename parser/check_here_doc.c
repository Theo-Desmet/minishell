/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:00:57 by tdesmet           #+#    #+#             */
/*   Updated: 2022/06/08 11:02:40 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unlink_file(t_data *data)
{
	char	*name;

	name = NULL;
	name = ft_strjoin2("/tmp/minishell", ft_itoa(data->act_heredoc));
	unlink(name);
	free(name);
}

void	ft_unlink_wrong_heredoc(t_data *data, t_token **args)
{
	int	i;

	i = 0;
	while (args[++i] && args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == R_HERE_DOC)
		{
			data->act_heredoc++;
			ft_unlink_file(data);
		}
	}
}

int	*ft_check_last_heredoc2(t_data *data, t_token **args, int cnt[2])
{
	int		i;
	int		multi_doc;

	i = -1;
	multi_doc = 0;
	while (args[++i] && args[i]->type != PIPE
		&& args[i]->type != D_PIPE && args[i]->type != D_AND)
	{
		if (args[i]->type == R_HERE_DOC)
		{
			if (multi_doc)
				ft_unlink_file(data);
			data->act_heredoc++;
			cnt[0] = i;
			multi_doc = 1;
		}
		if (args[i]->type == R_IN)
			cnt[1] = i;
	}
	return (cnt);
}

char	*ft_check_last_heredoc(t_data *data, t_token **args)
{
	int		cnt[2];
	char	*name;

	cnt[0] = -1;
	cnt[1] = -1;
	ft_check_last_heredoc2(data, args, cnt);
	name = ft_strjoin2("/tmp/minishell", ft_itoa(data->act_heredoc));
	if (cnt[0] > cnt[1])
		return (name);
	else
		return (free(name), NULL);
}
