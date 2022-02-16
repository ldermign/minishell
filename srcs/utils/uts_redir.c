/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:38:11 by ldermign          #+#    #+#             */
/*   Updated: 2022/02/16 13:52:12 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_first(char *args)
{
	return (ft_pos_strstr(args, ">") != -1
		|| ft_pos_strstr(args, "<") != -1
		|| ft_pos_strstr(args, ">>") != -1
		|| ft_pos_strstr(args, "<<") != -1);
}

int	only_right(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_pos_strstr(args[i], "<") != -1
			|| ft_pos_strstr(args[i], "<<") != -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	is_redir(char **args, char *str)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_pos_strstr(args[i], str) != -1)
			return (1);
		i++;
	}
	return (0);
}

int	last_redir(char **args)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (args[i])
	{
		if (args[i][1] != '\0' && (args[i][0] == '>' || args[i][0] == '<'))
		{
			if (args[i][0] == '>' && args[i][1] == '>' && args[i][2] == '\0')
				last = 3;
			if (args[i][0] == '<' && args[i][1] == '<' && args[i][2] == '\0')
				last = 4;
		}
		else if (args[i][0] == '>' && args[i][1] == '\0')
			last = 1;
		else if (args[i][0] == '<' && args[i][1] == '\0')
			last = 2;
		i++;
	}
	return (last);
}
