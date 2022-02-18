/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 06:38:09 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/18 06:52:52 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	pas fini

int	len_arg(char *line)
{
	int i;

	i = 0;
	while(line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '$')
			i += len_variable(&line[i]);
		else if (line[i] == 39)
			i += len_simple_quote(&line[i]);
		else if (line[i] == 34)
			i += len_double_quotes(&line[i]);
		else if (line[i] == 60 || line[i] == 62)
			i += pass_redirections(&line[i]);
		else
			i++;
		if (parsing->error == 1)
			return (-1);
		i++;
	}
	return (i);
}
