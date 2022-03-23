/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 04:37:53 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/23 05:30:19 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_simple_quote(char *line, char *str, t_struct *minish)
{
	int	i;

	i = 1;
	while (line[i] != 39)
	{
		str[minish->parsing.fill_arg++] = line[i];
		i++;
	}
	return (i);
}

int	fill_double_quotes(char *line, char *str, t_struct *minish)
{
	int	i;

	i = 1;
	minish->parsing.quotes = 1;
	while (line[i] != 34)
	{
		if (line[i] == '$')
			i += fill_variable(&line[i], str, minish);
		else
			str[minish->parsing.fill_arg++] = line[i];
		i++;
	}
	minish->parsing.quotes = 0;
	return (i);
}

int	fill_arg2(char *line, char *str, t_struct *minish)
{
	int	i;

	i = 0;
	minish->parsing.fill_arg = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '$')
			i += fill_variable(&line[i], str, minish);
		else if (line[i] == 39)
			i += fill_simple_quote(&line[i], str, minish);
		else if (line[i] == 34)
			i += fill_double_quotes(&line[i], str, minish);
		else if (line[i] == 60 || line[i] == 62)
			i += pass_redir(&line[i], minish) - 1;
		else
			str[minish->parsing.fill_arg++] = line[i];
		if (minish->parsing.error != 0)
			return (-1);
		i++;
	}
	str[minish->parsing.fill_arg] = '\0';
	return (i);
}
