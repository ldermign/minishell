/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:59:13 by elisa             #+#    #+#             */
/*   Updated: 2022/02/07 16:38:04 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// > 

void	check_char_in_file_name(char c, t_parsing *parsing)
{
	if (c == '(' || c == ')' || c == '`')
	{
		write(1, "syntax error near unexpected token `", 36);
		write(1, &c, 1);
		write(1, "'\n", 2);
		parsing->error = 1;
	}
}

void	parse_third_redir(char *line, t_parsing *parsing)
{
	if (parsing->red2 == 1)
		parsing->red2 = 0;
	parsing->red1 = 1;
	parsing->i_line++;
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	while (line[parsing->i_line] && line[parsing->i_line] != '|'
		&& line[parsing->i_line] != ' ')
	{
		if (line[parsing->i_line] == 34)
			double_quotes(line, parsing);
		else if (line[parsing->i_line] == 39)
			simple_quote(line, parsing);
		else if (line[parsing->i_line] == 60 || line[parsing->i_line] == 62)
			return ;
		else
			check_char_in_file_name(line[parsing->i_line], parsing);
		if (parsing->error == 1)
			return ;
		parsing->i_line++;
	}
}
