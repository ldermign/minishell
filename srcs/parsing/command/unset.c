/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:23:36 by elisa             #+#    #+#             */
/*   Updated: 2022/02/01 11:27:59 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_unset(char *line, t_parsing *parsing)
{
	if (error_check(line, parsing, 5) == -1)
		return ;
	printf(GREEN"unset ok\n"NORMAL);
}
