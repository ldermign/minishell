/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejahan <ejahan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 05:40:00 by ejahan            #+#    #+#             */
/*   Updated: 2022/02/20 08:11:49 by ejahan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_quotes(char *line)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	if (line[i] == line[j])
		return (i + 1);
	while (line[i] && line[i] != line[j])
		i++;
	return (i);
}

int	pass_redir(char *line, t_struct *minish)
{
	int	i;

	i = 1;
	if (line[i] == line[0])
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>' || line[i] == '\0')
	{
		if (line[i] == '\0')
			printf("syntax error near unexpected token `newline'\n");
		else
			printf("syntax error near unexpected token `%c'\n", line[i]);
		minish->parsing.error = 1;
		return (-1);
	}
	while (line[i] && line[i] != ' ')
		i++;
	return (i);
}

int	pass_variable(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != 39 && line[i] != 34
		&& line[i] != '<' && line[i] != '>' && line[i] != ' ')
		i++;
	return (i - 1);
}

int	is_variable_char(char c)
{
	if (c == ' ' || c == 34 || c == 39 || c == '|' || c == '$' || c == '\0'
		|| c == '<' || c == '>' || c == '{')
		return (1);
	return (0);
}

int	error_malloc(t_struct *minish)
{
	printf("error malloc\n");
	minish->parsing.error = 1;
	return (-1);
}
