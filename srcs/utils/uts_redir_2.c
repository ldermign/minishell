/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uts_redir_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:21:18 by ldermign          #+#    #+#             */
/*   Updated: 2022/03/06 19:56:11 by ejahan           ###   ########.fr       */
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
		if (args[i][0] == '>')
		{
			if (args[i][1] == '\0')
				last = i;
			else if (args[i][1] && args[i][1] == '>' && args[i][2] == '\0')
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
		if (args[i][0] == '<')
		{
			if (args[i][1] == '\0')
				last = i;
			else if (args[i][1] && args[i][1] == '<' && args[i][2] == '\0')
				last = i;
		}
		i++;
	}
	return (last);
}
