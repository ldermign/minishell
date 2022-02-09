/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:22:54 by elisa             #+#    #+#             */
/*   Updated: 2022/02/08 11:29:42 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_export(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 6) == -1)
		return ;
	while (line[parsing->i_line] && line[parsing->i_line] != '|'
		&& line[parsing->i_line] != '>' && line[parsing->i_line] != '<')
		parsing->i_line++;
}
