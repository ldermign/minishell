/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_redir_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:21:18 by ldermign          #+#    #+#             */
/*   Updated: 2022/04/01 11:20:15 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pos_last_redir_right(char **args)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (args[i])
	{
		if (args[i][0] && args[i][0] == '>')
		{
			if ((args[i][1] && args[i][1] != '>')
			|| (args[i][1] && args[i][2] && args[i][1] == '>'
				&& args[i][2] != '>'))
				last = i;
		}
		i++;
	}
	return (last);
}

int	pos_last_redir_left(char **args)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (args[i])
	{
		if (args[i][0] && args[i][0] == '<')
		{
			if (args[i][1] && args[i][1] != '<')
				last = i;
		}
		i++;
	}
	return (last);
}

char	*recup_name(char *args)
{
	char	*name;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	while (args[i] && args[i] != ' ')
		i++;
	i++;
	while (args[i + j])
		j++;
	name = malloc(sizeof(char) * j + 1);
	if (name == NULL)
		return (NULL);
	name[j] = '\0';
	while (k < j)
		name[k++] = args[i++];
	return (name);
}

int	is_built_in(char *str)
{
	if (ft_memcmp(str, "echo", 5) == 0
		|| ft_memcmp(str, "pwd", 4) == 0
		|| ft_memcmp(str, "env", 4) == 0
		|| ft_memcmp(str, "export", 7) == 0
		|| ft_memcmp(str, "unset", 6) == 0
		|| ft_memcmp(str, "cd", 3) == 0
		|| ft_memcmp(str, "exit", 5) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
