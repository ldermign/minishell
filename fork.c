/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldermign <ldermign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:17:23 by ldermign          #+#    #+#             */
/*   Updated: 2021/12/14 13:31:23 by ldermign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fct_debut_liena_chaipa(void)
{
	char	*line;

	line = NULL;
	write(0, "$ ", 2);
	while (get_next_line(0, &line) > 0)
	{
		write(0, "$ ", 2);
	}
	return (0);
}