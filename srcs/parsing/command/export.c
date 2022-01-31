/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:22:54 by elisa             #+#    #+#             */
/*   Updated: 2022/01/31 13:26:18 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_export(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 6) == -1)
		return ;
	// printf(GREEN"export ok\n"NORMAL);
}

// https://www.tutorialspoint.com/unix_commands/export.htm
