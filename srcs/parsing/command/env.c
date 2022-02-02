/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisa <elisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:24:56 by elisa             #+#    #+#             */
/*   Updated: 2022/01/25 11:27:33 by elisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf(GREEN"env ok\n"NORMAL);
}
