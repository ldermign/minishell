/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:24:56 by elisa             #+#    #+#             */
/*   Updated: 2022/02/07 16:24:46 by ejahan           ###   ########.fr       */
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
}
