/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:08:31 by elisa             #+#    #+#             */
/*   Updated: 2022/01/09 23:22:29 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	error_check(char *line, t_parsing *parsing, int i)
{
	if (line[parsing->i_line + i] != ' '
		&& line[parsing->i_line + i] != '\0')
	{
		error_command(line, parsing, " : command not found");
		return (-1);
	}
	parsing->i_line += i;
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	return (0);
}

int	error_command(char *line, t_parsing *parsing, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[parsing->i_line + i] && line[parsing->i_line + i] != ' ')
		i++;
	parsing->ret_error = malloc(sizeof(char) * i + 21);
	if (parsing->ret_error == NULL)
		return (-1);
	while (j < i)
	{
		parsing->ret_error[j] = line[parsing->i_line + j];
		j++;
	}
	i = 0;
	while (str[i])
	{
		parsing->ret_error[j + i] = str[i];
		i++;
	}
	parsing->ret_error[i + j] = '\0';
	return (0);
}
