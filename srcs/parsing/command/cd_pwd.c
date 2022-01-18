/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:21:51 by elisa             #+#    #+#             */
/*   Updated: 2022/01/13 16:46:54 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_cd(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 2) == -1)
		return ;
	printf(GREEN"cd ok\n"NORMAL);
}

void	parse_pwd(char *line, t_parsing *parsing)
{
	char	*var;

	if (error_check(line, parsing, 3) == -1)
		return ;
	var = getenv("PWD");
	parsing->result = malloc(sizeof(char) * ft_strlen(var) + 1);
	if (parsing->result == NULL)
		return ;
	ft_strcpy(parsing->result, var);
	while (line[parsing->i_line] && (line[parsing->i_line] != '|'
		|| line[parsing->i_line] != '>' || line[parsing->i_line] != '<'))
		parsing->i_line++;
	parsing->pwd = 1;
	printf(GREEN"pwd ok\n"NORMAL);
}
