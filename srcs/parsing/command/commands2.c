/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:21:51 by elisa             #+#    #+#             */
/*   Updated: 2022/02/10 14:46:57 by ejahan           ###   ########.fr       */
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
}

void	parse_pwd(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 3) == -1)
		return ;
	while (line[parsing->i_line] && (line[parsing->i_line] != '|'
			|| line[parsing->i_line] != '>' || line[parsing->i_line] != '<'))
		parsing->i_line++;
}

void	parse_env(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 3) == -1)
		return ;
	if (line[parsing->i_line] != '\0' && line[parsing->i_line] != '|'
		&& line[parsing->i_line] != '<' && line[parsing->i_line] != '>')
	{
		printf("error : env : wrong arguments\n");
		parsing->error = 1;
		return ;
	}
}

void	parse_export(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 6) == -1)
		return ;
	while (line[parsing->i_line] && line[parsing->i_line] != '|'
		&& line[parsing->i_line] != '>' && line[parsing->i_line] != '<')
		parsing->i_line++;
}

void	parse_unset(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 5) == -1)
		return ;
	while (line[parsing->i_line] && line[parsing->i_line] != '|'
		&& line[parsing->i_line] != '>' && line[parsing->i_line] != '<')
		parsing->i_line++;
}
