/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:08:31 by elisa             #+#    #+#             */
/*   Updated: 2022/01/25 11:23:59 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_check(char *line, t_parsing *parsing, int i)
{
	if (line[parsing->i_line + i] != ' '
		&& line[parsing->i_line + i] != '\0')
	{
		error_command(line, parsing);
		return (-1);
	}
	parsing->i_line += i;
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	return (0);
}

void	error_command(char *line, t_parsing *parsing)
{
	write(1, "error : ", 8);
	while (line[parsing->i_line] && line[parsing->i_line] != ' ')
	{
		ft_putchar(line[parsing->i_line]);
		parsing->i_line++;
	}
	printf(": command not found\n");
	parsing->error = 1;
}
