/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:59:13 by elisa             #+#    #+#             */
/*   Updated: 2022/02/02 14:01:08 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 	60 <	62 >

// int	check_error_red(char *line, t_parsing *parsing)
// {
//     // flemme la j'avoue
// }

void	redirections(char *line, t_parsing *parsing)
{
	// if (check_error_red(line, parsing) == -1)
	// {
	// 	parsing->error = 1;
	// 	return ;
	// }
	if (line[parsing->i_line] == 60 && line[parsing->i_line + 1] != 60)
		first_redir(line, parsing);
	if (line[parsing->i_line] == 60 && line[parsing->i_line + 1] == 60)
		second_redir(line, parsing);
// 	if (line[parsing->i_line] == 62 && line[parsing->i_line + 1] != 62)
// 		third_redir(line, parsing);
// 	if (line[parsing->i_line] == 62 && line[parsing->i_line + 1] == 62)
// 		fourth_redir(line, parsing);
}

void	skip_redirections(char *line, t_parsing *parsing)
{
	while (line[parsing->i_line] == 60 || line[parsing->i_line] == 62
		|| line[parsing->i_line] == ' ')
		parsing->i_line++;
	if (line[parsing->i_line] == 34 || line[parsing->i_line] == 39)
	{
		parsing->i_line++;
		while (line[parsing->i_line] != 34 && line[parsing->i_line] != 39)
			parsing->i_line++;
		parsing->i_line++;
	}
	else
	{
		while (line[parsing->i_line] && line[parsing->i_line] != ' ')
			parsing->i_line++;
	}
	while (line[parsing->i_line] == ' ')
		parsing->i_line++;
	parsing->i_line--;
	printf("redir : [%s]\n", &line[parsing->i_line]);
}
