/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 06:38:09 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/08 07:33:55 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_simple_quote(char *line, t_struct *minish)
{
	int	i;

	i = 1;
	while (line[i] != 39)
	{
		i++;
		minish->parsing.len_arg++;
	}
	return (i);
}

int	len_double_quotes(char *line, t_struct *minish)
{
	int	i;

	i = 1;
	minish->parsing.quotes = 1;
	while (line[i] != 34)
	{
		if (line[i] == '$')
			i += len_variable(&line[i], minish);
		else
			minish->parsing.len_arg++;
		i++;
		if (minish->parsing.error != 0)
			return (-1);
	}
	minish->parsing.quotes = 0;
	return (i);
}

int	len_arg(char *line, t_struct *minish)
{
	int	i;

	i = 0;
	minish->parsing.len_arg = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '<' || line[i] == '>')
		i += pass_redir(&line[i], minish);
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '$')
			i += len_variable(&line[i], minish);
		else if (line[i] == 39)
			i += len_simple_quote(&line[i], minish);
		else if (line[i] == 34)
			i += len_double_quotes(&line[i], minish);
		else if (line[i] == 60 || line[i] == 62)
			i += (pass_redir(&line[i], minish) - 1);
		else
			minish->parsing.len_arg++;
		if (minish->parsing.error != 0)
			return (-1);
		i++;
	}
	return (i);
}
