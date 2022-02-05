/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:21:51 by elisa             #+#    #+#             */
/*   Updated: 2022/01/25 14:13:27 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cd(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 2) == -1)
		return ;
	while (line[parsing->i_line] && line[parsing->i_line] != '|'
		&& line[parsing->i_line] != '>' && line[parsing->i_line] != '<')
		parsing->i_line++;
	// printf(GREEN"cd ok\n"NORMAL);
}

void	parse_pwd(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 3) == -1)
		return ;
	while (line[parsing->i_line] && (line[parsing->i_line] != '|'
		|| line[parsing->i_line] != '>' || line[parsing->i_line] != '<'))
		parsing->i_line++;
	// printf(GREEN"pwd ok\n"NORMAL);
}
