/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 05:13:08 by ejahan            #+#    #+#             */
/*   Updated: 2022/03/08 07:33:05 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_arg_count2(char *line, t_struct *minish, int i)
{
	while (line[i])
	{
		while (line[i] && line[i] != 39 && line[i] != 34
			&& line[i] != ' ' && line[i] != '$')
			i++;
		if (line[i] == 39 || line[i] == 34)
			i += pass_quotes(&line[i]);
		else if (line[i] == '$')
			i += pass_variable(&line[i]);
		else if (line[i] == '\0' || line[i] == ' ')
			return (i);
		if (minish->parsing.error != 0)
			return (-1);
		i++;
	}
	return (i);
}

int	pass_arg_count_else_if(char *line, int i, t_struct *minish)
{
	int	j;

	j = is_empty(&line[i], minish);
	if (j != 0)
		minish->parsing.nb_arg++;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == 39 || line[i] == 34)
			i += pass_quotes(&line[i]);
		i++;
	}
	return (i);
}

int	pass_arg_count(char *line, t_struct *minish)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '<' || line[i] == '>')
		return (pass_redir(&line[i], minish) + i);
	else if (line[i] == '\0')
		return (i);
	else if (line[i] == '$' && line[i + 1] == '?')
	{
		minish->parsing.nb_arg++;
		while (line[i] && line[i] != ' ')
		{
			if (line[i] == 39 || line[i] == 34)
				i += pass_quotes(&line[i]);
			i++;
		}
		return (i);
	}
	else if (line[i] == '$')
		return (pass_arg_count_else_if(line, i, minish));
	minish->parsing.nb_arg++;
	return (pass_arg_count2(line, minish, i));
}

int	count_redir(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			j++;
			while (line[i] == '<' || line[i] == '>' || line[i] == ' ')
				i++;
			while (line[i] && line[i] != '<' && line[i] != '>')
				i++;
		}
		else
			i++;
	}
	return (j);
}
