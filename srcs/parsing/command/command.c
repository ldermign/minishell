/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:59:13 by elisa             #+#    #+#             */
/*   Updated: 2022/02/02 14:01:08 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_option(char *line, t_parsing *parsing)
{
	if (ft_strlen(&line[parsing->i_line]) > 1
		&& ft_memcmp("-n", &line[parsing->i_line], 2) == 0)
	{
		if (line[parsing->i_line + 2] != '\0'
			&& line[parsing->i_line + 2] != ' ')
			return ;
		parsing->option = 1;
		parsing->i_line += 2;
		while (line[parsing->i_line] == ' ')
			parsing->i_line++;
	}
}

void	parse_echo(char *line, t_parsing *parsing)
{
	int	i;
	int	tmp;

	if (error_check(line, parsing, 4) == -1)
		return ;
	check_option(line, parsing);
	tmp = parsing->i_line;
	i = find_len(line, parsing);
	if (i == -1)
		return ;
	parsing->result = malloc(sizeof(char) * i + 1);
	if (parsing->result == NULL)
	{
		parsing->error = 1;
		return ;
	}
	parsing->i_line = tmp;
	fill_result(line, parsing);
	printf("to_print : [%s]\n", parsing->result);
	printf(GREEN"echo ok\n"NORMAL);
}

void	parse_exit(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 4) == -1)
		return ;
	printf(GREEN"exit ok\n"NORMAL);
}
