/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:38:11 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/11 10:18:57 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_first(char *args)
{
	if (ft_pos_strstr(args, ">") != -1 || ft_pos_strstr(args, "<") != -1
		|| ft_pos_strstr(args, ">>") != -1 || ft_pos_strstr(args, "<<") != -1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
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

// int	last_redir(char **args)
// {
// 	int	i;
// 	int	last;

// 	i = 0;
// 	last = -1;
// 	while (args[i])
// 	{
// 		if (args[i][1] != '\0' && (args[i][0] == '>' || args[i][0] == '<'))
// 		{
// 			if (args[i][0] == '>' && args[i][1] == '>' && args[i][2] == '\0')
// 				last = 3;
// 			if (args[i][0] == '<' && args[i][1] == '<' && args[i][2] == '\0')
// 				last = 4;
// 		}
// 		else if (args[i][0] == '>' && args[i][1] == '\0')
// 			last = 1;
// 		else if (args[i][0] == '<' && args[i][1] == '\0')
// 			last = 2;
// 		i++;
// 	}
// 	return (last);
// }

int	last_redir(char **args)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (args[i])
	{
		if (args[i][1] != ' ' && (args[i][0] == '>' || args[i][0] == '<'))
		{
			if (args[i][0] == '>' && args[i][1] == '>' && args[i][2])
				last = 3;
			if (args[i][0] == '<' && args[i][1] == '<' && args[i][2])
				last = 4;
		}
		else if (args[i][0] == '>')
			last = 1;
		else if (args[i][0] == '<')
			last = 2;
		i++;
	}
	return (last);
}

int	is_built_in(char *str)
{
	if (ft_memcmp(str, "echo", 4) == 0 || ft_memcmp(str, "pwd", 4) == 0
		|| ft_memcmp(str, "env", 4) == 0
		|| ft_memcmp(str, "export", 7) == 0
		|| ft_memcmp(str, "unset", 6) == 0
		|| ft_memcmp(str, "echo", 5) == 0
		|| ft_memcmp(str, "exit", 5) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
