/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:59:13 by elisa             #+#    #+#             */
/*   Updated: 2022/02/05 18:18:33 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_fourth_redir(char *line, t_parsing *parsing)	// >> 
{
	if (parsing->red1 == 1)
		parsing->red1 = 0;
	parsing->red2 = 1;
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
