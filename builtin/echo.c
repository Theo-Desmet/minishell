/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 00:13:37 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/29 00:13:37 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_check_option(char **args)
{
	return (!ft_strncmp(*args, "-n", ft_strlen(*args)));
}

int	ft_echo(char **args)
{
	int	n;
	int	limit;
	int	i;

	if (!args)
	{
		printf("\n");
		return (1);
	}
	n = ft_check_option(args);
	limit = 0;
	while (args[limit])
		limit++;
	i = 0;
	if (n)
		i = 1;
	while (i < limit)
	{
		printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (!n)
		printf("\n");
	return (1);
}
